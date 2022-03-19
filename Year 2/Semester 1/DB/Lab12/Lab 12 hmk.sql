DROP DATABASE DummyDB
GO
CREATE DATABASE DummyDB
GO
USE DummyDB
GO

CREATE TABLE Persons (
	person_id INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
	first_name NVARCHAR(100) NOT NULL,
	last_name NVARCHAR(100) NOT NULL,
	born_date DATE NOT NULL
)

CREATE TABLE Cars (
	car_id INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
	person_id INT NULL,
	model NVARCHAR(100) NOT NULL,
	year_of_fabrication INT NOT NULL,
	CONSTRAINT FK_Cars_PersonId FOREIGN KEY (person_id) REFERENCES Persons(person_id)
)

CREATE TABLE Locations(
	adress  NVARCHAR(100) NOT NULL,
	postal_code INT NOT NULL,
	field_size INT NULL DEFAULT 0,
	CONSTRAINT PK_Locations_AdressPostalCode PRIMARY KEY (
		adress,
		postal_code
	)

)
GO

DROP VIEW PersonsBornBefore2000 
GO

CREATE VIEW PersonsBornBefore2000 AS
SELECT * FROM Persons
WHERE born_date < '20000101'
GO

CREATE VIEW GetPersonsAndTheirCars AS
SELECT P.first_name, P.last_name, C.model FROM Persons P, Cars C
WHERE P.person_id = C.person_id
GO

CREATE VIEW GetPersonsThatHaveAtleastACar AS
SELECT P.person_id FROM Persons P, Cars C
WHERE P.person_id = C.car_id
GROUP BY P.person_id
GO

SELECT * FROM Tests
GO

INSERT INTO Tests(Name) VALUES('Test1')
INSERT INTO Tests(Name) VALUES('Test2')
GO

-- set so nr of rows affected stop showing
SET NOCOUNT OFF
GO

DROP PROCEDURE usp_RunTest
GO

-- run ALTER TABLE [TableName] REBUILD WITH (IGNORE_DUP_KEY = ON) so you eliminate the chances of running a test with the duplicate key error
CREATE PROCEDURE usp_RunTest(@TestName NVARCHAR(50))
AS
	-- starting the big timer
	DECLARE @BigStartTimer DATETIME
	DECLARE @BigEndTimer DATETIME
	DECLARE @Description NVARCHAR(2000)
	SET @Description=''
	SET @BigStartTimer= GETDATE()

	-- getting the id of the test with the given name
	DECLARE @TestIDNr INT
	SELECT @TestIDNr=T.TestID FROM Tests T WHERE T.Name = @TestName
	
	-- creating a new entry in TestRuns so i have the TestRunID to work with
	DECLARE @TestRunIDNr INT
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES (NULL, NULL, NULL)
	SELECT @TestRunIDNr = SCOPE_IDENTITY()

	PRINT( 'The test ' + @TestName + ' with id ' + CAST(@TestIDNr AS NVARCHAR) + ' has received the TestRun entry with value ' + CAST(@TestRunIDNr AS NVARCHAR))

	-- declaring general variables that i will use multiple times in multiple places
	DECLARE @StartAtVar DATETIME
	DECLARE @EndAtVar DATETIME
	DECLARE @TableIDNr INT
	DECLARE @TableName NVARCHAR(50)
	

	-- declaring the cursor for deleting all the data in all tables (tied to the test)
	DECLARE db_cursor_deleteDataFromTables CURSOR FOR
	SELECT TableID 
	FROM [TestTables]
	WHERE TestID = @TestIDNr
	ORDER BY Position ASC

	OPEN db_cursor_deleteDataFromTables

	-- fetching the first table to delete data from
	FETCH NEXT FROM db_cursor_deleteDataFromTables INTO @TableIDNr

	WHILE @@FETCH_STATUS = 0
	BEGIN
		
		-- getting the table name
		SELECT @TableName=[Name] FROM [Tables] WHERE TableID = @TableIDNr

		-- adding to the description
		SET @Description=@Description + @TableName + ', '

		-- deleting the data
		EXEC('DELETE FROM ' + @TableName)
		
		PRINT('Deleted data from table with name ' + @TableName + ' and id ' + CAST(@TableIDNr AS NVARCHAR))

		-- fetching the netx table id to delete data from
		FETCH NEXT FROM db_cursor_deleteDataFromTables INTO @TableIDNr
	END;

	CLOSE db_cursor_deleteDataFromTables
	DEALLOCATE db_cursor_deleteDataFromTables


	-- INSERTING DATA INTO TABLES !!!!!! LET THE FUN BEGIN

	-- declaring variables that i use for inserting data
	DECLARE @NrOfRows INT
	
	DECLARE @columnName NVARCHAR(255)
	DECLARE @columnType NVARCHAR(55)
	DECLARE @columnLength INT
	DECLARE @isIdentity BIT
	DECLARE @insertStmt NVARCHAR(2000)
	DECLARE @isForeignKey INT
	DECLARE @RefTable NVARCHAR(255)
	DECLARE @RefColumn NVARCHAR(255)
	DECLARE @RandomPKForFKInt INT
	DECLARE @RandomPKForFKNVarChar NVARCHAR(255)
	DECLARE @RandomPKForFKDate DATE
	DECLARE @resultINT TABLE (rowVal INT);
	DECLARE @resultNVARCHAR TABLE (rowVal NVARCHAR);
	DECLARE @resultDATE TABLE (rowVal DATE);
	DECLARE @count INT 


	-- declaring the cursor that will insert the data in all the tables
	DECLARE us_insertDataInTablesCursor CURSOR FOR
	SELECT TableID FROM TestTables
	WHERE TestID = @TestIDNr
	ORDER BY Position DESC

	-- opening the curosr for inserting data
	OPEN us_insertDataInTablesCursor

	-- getting the first table to insert data into
	FETCH NEXT FROM us_insertDataInTablesCursor INTO @TableIDNr

	WHILE @@FETCH_STATUS = 0
	BEGIN
	

		-- getting the number of rows that i will insert
		SELECT @NrOfRows = NoOfRows FROM TestTables WHERE TableID = @TableIDNr AND TestID = @TestIDNr

		-- getting the name of the table
		SELECT @TableName=[Name] FROM [Tables] WHERE TableID = @TableIDNr

		-- Starting the timer
		SET @StartAtVar = GETDATE()

		-- restarting count for how many rows to insert
		SET @count = 0

		-- inserting data into the table
		WHILE @count < @NrOfRows
		BEGIN

			SET @insertStmt = 'INSERT INTO ' + @TableName + ' VALUES ('

			DECLARE us_testCursor CURSOR FOR
			SELECT COLUMN_NAME 
			FROM INFORMATION_SCHEMA.COLUMNS
			WHERE TABLE_NAME = @TableName

			OPEN us_testCursor

			FETCH NEXT FROM us_testCursor INTO @columnName

			WHILE @@FETCH_STATUS = 0
			BEGIN
				-- getting the info if it is identity or not
				SELECT @isIdentity=columnproperty(object_id(@TableName), @columnName,'IsIdentity')
	
				-- if it is identity, go to the next column
				IF @isIdentity = 1
				BEGIN
					FETCH NEXT FROM us_testCursor INTO @columnName
					CONTINUE
				END

				-- getting the type of the column
				SELECT @columnType = DATA_TYPE FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = @TableName AND COLUMN_NAME = @columnName

				-- checking if the column is a foreign key or not
				SELECT 
				@isForeignKey = COUNT(*)
				FROM 
					sys.foreign_keys AS f
				INNER JOIN 
					sys.foreign_key_columns AS fc 
						ON f.OBJECT_ID = fc.constraint_object_id
				INNER JOIN 
					sys.tables t 
						ON t.OBJECT_ID = fc.referenced_object_id
				WHERE 
					f.parent_object_id = OBJECT_ID(@TableName) AND COL_NAME(fc.parent_object_id,fc.parent_column_id) = @columnName

				-- if @isForeignKey is 1, it means that there is a foreign key constraint on that column
				IF @isForeignKey = 1
				BEGIN
		
					-- getting the referenced table and column
					SELECT 
						@RefTable = OBJECT_NAME(f.referenced_object_id),
						@RefColumn = COL_NAME(fc.parent_object_id,fc.parent_column_id)
					FROM 
						sys.foreign_keys AS f
					INNER JOIN 
						sys.foreign_key_columns AS fc 
							ON f.OBJECT_ID = fc.constraint_object_id
					INNER JOIN 
						sys.tables t 
							ON t.OBJECT_ID = fc.referenced_object_id
					WHERE 
						f.parent_object_id = OBJECT_ID(@TableName) AND COL_NAME(fc.parent_object_id,fc.parent_column_id) = @columnName

					IF @columnType = 'int' OR @columnType = 'long'
					BEGIN
						INSERT INTO @resultINT (rowVal)
						EXEC('SELECT ' + @RefColumn +' FROM (
								SELECT ROW_NUMBER() OVER(ORDER BY '+@RefColumn+') [row], '+@RefColumn+'
								FROM '+@RefTable+'
							) t 
							WHERE t.row = 1 + (SELECT CAST(RAND() * COUNT(*) as INT) FROM '+@RefTable+')');
						SET @RandomPKForFKInt = (select top (1) rowVal from @resultINT);
			
						SET @insertStmt = @insertStmt + CAST(@RandomPKForFKInt as NVARCHAR)
					END
					ELSE 
					BEGIN
						IF @columnType = 'nvarchar' OR @columnType = 'varchar'
						BEGIN
							INSERT INTO @resultNVARCHAR (rowVal)
							EXEC('SELECT ' + @RefColumn +' FROM (
									SELECT ROW_NUMBER() OVER(ORDER BY '+@RefColumn+') [row], '+@RefColumn+'
									FROM '+@RefTable+'
								) t 
								WHERE t.row = 1 + (SELECT CAST(RAND() * COUNT(*) as INT) FROM '+@RefTable+')');
							SET @RandomPKForFKNVarChar = (select top (1) rowVal from @resultNVARCHAR);
			
							SET @insertStmt = @insertStmt + '''' + @RandomPKForFKNVarChar + ''''
						END
						ELSE 
						BEGIN
							IF @columnType = 'date'
							BEGIN
								INSERT INTO @resultDATE (rowVal)
								EXEC('SELECT ' + @RefColumn +' FROM (
										SELECT ROW_NUMBER() OVER(ORDER BY '+@RefColumn+') [row], '+@RefColumn+'
										FROM '+@RefTable+'
									) t 
									WHERE t.row = 1 + (SELECT CAST(RAND() * COUNT(*) as INT) FROM '+@RefTable+')');
								SET @RandomPKForFKDate = (select top (1) rowVal from @resultDATE) ;

								SET @insertStmt = @insertStmt +'''' + CAST(@RandomPKForFKDate as NVARCHAR)+'''' 
							END
						END
					END

				END
				ELSE
				BEGIN

					IF @columnType = 'int' OR @columnType = 'long'
					BEGIN
						SET @insertStmt = @insertStmt + CAST( dbo.createRandomInteger() as NVARCHAR) 
					END
					ELSE 
					BEGIN
						IF @columnType = 'nvarchar' OR @columnType = 'varchar'
						BEGIN
							-- getting the length of the column
							SELECT @columnLength=CHARACTER_MAXIMUM_LENGTH FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = @TableName AND COLUMN_NAME = @columnName
			
							SET @insertStmt = @insertStmt + '''' +dbo.createRandomNVARCHAR(@columnLength) + ''''
						END
						ELSE 
						BEGIN
							IF @columnType = 'date'
							BEGIN
								SET @insertStmt = @insertStmt +'''' + CAST(dbo.createRandomDate() as NVARCHAR)+'''' 
							END
						END
					END
				END
				FETCH NEXT FROM us_testCursor INTO @columnName

				-- ending the insert stmt
				IF @@FETCH_STATUS != 0
					SET @insertStmt = @insertStmt + ')'
				ELSE
					SET @insertStmt = @insertStmt + ','

			END
			EXEC(@insertStmt)

			CLOSE us_testCursor
			DEALLOCATE us_testCursor

			SET @count = @count + 1
		END


		--ending the timer
		SET @EndAtVar = GETDATE()

		PRINT('Inserted data into table with name ' + @TableName +' and id ' + CAST(@TableIDNr AS NVARCHAR) + ' and it took from ' + format(@StartAtVar, 'yyyy-MM-dd HH:mm:ss.fff') + ' until ' + format(@EndAtVar, 'yyyy-MM-dd HH:mm:ss.fff'))

		--inserting the date obtained for insert test
		INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt)
		VALUES (@TestRunIDNr, @TableIDNr, @StartAtVar, @EndAtVar)

		-- getting the next table to work on
		FETCH NEXT FROM us_insertDataInTablesCursor INTO @TableIDNr
	
	END

	-- closing the inserting part
	CLOSE us_insertDataInTablesCursor
	DEALLOCATE us_insertDataInTablesCursor

	-- declaring the variables i will use in the view testing
	DECLARE @ViewIDNr INT
	DECLARE @ViewName NVARCHAR(50)

	

	-- creating cursor for going trough the views associated to the test id, one at a time
	DECLARE db_cursor_view CURSOR FOR -- declaring cursor
	SELECT TV.ViewID  -- populating the cursor
	FROM TestViews TV
	WHERE TV.TestID = @TestIDNr

	-- opening the cursor
	OPEN db_cursor_view

	-- fetch the next record
	FETCH NEXT FROM db_cursor_view INTO @ViewIDNr

	WHILE @@FETCH_STATUS = 0
	BEGIN
		
		-- getting the view name to execute 
		SELECT @ViewName = V.Name FROM [Views] V WHERE V.ViewID = @ViewIDNr
		
		-- adding to the description
		SET @Description=@Description + @ViewName + ', '

		-- StartAt
		SELECT @StartAtVar=GETDATE()

		--executing the view
		EXEC('SELECT * FROM ' + @ViewName)

		--EndAt
		SELECT @EndAtVar=GETDATE()

		-- Inserting the data gathered
		INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) 
		VALUES(@TestRunIDNr, @ViewIDNr, @StartAtVar, @EndAtVar)

		-- printing beautiful message
		PRINT('Test on the view ' + @ViewName + ' with id ' + CAST(@ViewIDNr AS NVARCHAR) + ' ran from ' + format(@StartAtVar, 'yyyy-MM-dd HH:mm:ss.fff') + ' until ' + format(@EndAtVar, 'yyyy-MM-dd HH:mm:ss.fff'))

		-- fetch the next record from the cursor
		FETCH NEXT FROM db_cursor_view INTO @ViewIDNr

	END;
	
	-- closing and deallocating the view
	CLOSE db_cursor_view;
	DEALLOCATE db_cursor_view;
	
	SET @BigEndTimer= GETDATE()

	--updating the test run
	UPDATE TestRuns SET [Description]=@Description, StartAt=@BigStartTimer, EndAt=@BigEndTimer WHERE TestRunID= @TestRunIDNr

GO


-- inserting tables
INSERT INTO [Tables]([Name]) VALUES ('Persons')
INSERT INTO [Tables]([Name]) VALUES ('Cars')
INSERT INTO [Tables]([Name]) VALUES ('Locations')
SELECT * FROM [Tables]

-- inserting connections between tests and tables
INSERT INTO [TestTables](TestID, TableID, NoOfRows, Position)
VALUES (1, 2, 10, 1)
INSERT INTO [TestTables](TestID, TableID, NoOfRows, Position)
VALUES (1, 1, 8, 2)
INSERT INTO [TestTables](TestID, TableID, NoOfRows, Position)
VALUES (2, 2, 10, 1)
INSERT INTO [TestTables](TestID, TableID, NoOfRows, Position)
VALUES (2, 1, 8, 2)
INSERT INTO [TestTables](TestID, TableID, NoOfRows, Position)
VALUES (2, 3, 25, 3)
SELECT * FROM TestTables


-- inserting views
INSERT INTO [Views]([Name]) VALUES('PersonsBornBefore2000')
INSERT INTO [Views]([Name]) VALUES('GetPersonsAndTheirCars')
INSERT INTO [Views]([Name]) VALUES('GetPersonsThatHaveAtleastACar')
SELECT * FROM [Views]
GO

-- making connection between tests and views
INSERT INTO [TestViews]([TestID], [ViewID]) VALUES (1, 1)
INSERT INTO [TestViews]([TestID], [ViewID]) VALUES (1, 3)
INSERT INTO [TestViews]([TestID], [ViewID]) VALUES (2, 1)
INSERT INTO [TestViews]([TestID], [ViewID]) VALUES (2, 3)
INSERT INTO [TestViews]([TestID], [ViewID]) VALUES (2, 2)
SELECT * FROM [TestViews]
GO

SELECT * FROM Tests
SELECT * FROM TestRuns
SELECT * FROM [TestRunViews]
SELECT * FROM TestRunTables

SELECT * From Persons
SELECT * From Cars
SELECT * From Locations

DELETE FROM TestRuns

DBCC CHECKIDENT ('[TestRuns]', RESEED, 0);
GO

ALTER TABLE Persons
ADD Phone NVARCHAR(10) DEFAULT ''


ALTER TABLE Persons
DROP COLUMN Phone

SET NOCOUNT ON
EXEC usp_RunTest 'Test1'
GO


EXEC usp_RunTest 'Test2'
GO





CREATE VIEW us_randomNumberView AS
SELECT RAND() as random_number
GO

DROP VIEW us_randomNumberView
GO

CREATE FUNCTION createRandomInteger()
RETURNS INT AS
BEGIN
	DECLARE @decimal FLOAT
	DECLARE @value INT
	SELECT @decimal = random_number FROM us_randomNumberView
	SET @value = @decimal * 10000 + 1
	RETURN @value
END

DROP FUNCTION createRandomInteger

PRINT(dbo.createRandomInteger())

GO

DROP FUNCTION createRandomNVARCHAR

CREATE FUNCTION dbo.createRandomNVARCHAR(@length INT)
RETURNS NVARCHAR(255) AS
BEGIN
	DECLARE @string NVARCHAR(255)
	SET @string = ''
	DECLARE @value FLOAT
	WHILE @length > 0
		BEGIN
		SELECT @value = random_number FROM us_randomNumberView
		SET @string = @string + CHAR(CAST(@value * 96 + 40 as INT))
		SET @length = @length - 1
		END
	RETURN @string

END


PRINT(dbo.createRandomNVARCHAR(55))
GO

CREATE FUNCTION createRandomDate()
RETURNS DATE AS
BEGIN
	DECLARE @date DATETIME
	DECLARE @value FLOAT
	SELECT @value = random_number FROM us_randomNumberView
	SET @date = GETDATE() + (365 * 2 * @value - 365)
	RETURN @date
END

DROP FUNCTION createRandomDate


PRINT(dbo.createRandomDate())
GO

PRINT(dbo.randomIntRow('Persons', 'person_id'))

-- random row
DECLARE @username VARCHAR(50)
SELECT @username = [person_id] FROM (
    SELECT ROW_NUMBER() OVER(ORDER BY person_id) [row], [person_id]
    FROM Persons
) t 
WHERE t.row = 1 + (SELECT CAST(RAND() * COUNT(*) as INT) FROM Persons)

print(@username)



DECLARE @str NVARCHAR(1000)
SET @str='INSERT INTO Persons VALUES(dbo.createRandomNVARCHAR(70), dbo.createRandomNVARCHAR(55), dbo.createRandomDate())'
EXEC(@str)
SELECT * FROM Persons
GO

DECLARE @TableName NVARCHAR(255)
SET @TableName= 'Cars'



GO

SELECT * FROM Persons
SELECT * FROM Cars


	select *
from INFORMATION_SCHEMA.COLUMNS
where TABLE_NAME='Persons'

SELECT 
   OBJECT_NAME(f.parent_object_id) TableName,
   COL_NAME(fc.parent_object_id,fc.parent_column_id) ColName,
   OBJECT_NAME(f.referenced_object_id) ReferencedTable,
   COL_NAME(fc.referenced_object_id, fc.referenced_column_id) ReferencedColumn
FROM 
   sys.foreign_keys AS f
INNER JOIN 
   sys.foreign_key_columns AS fc 
      ON f.OBJECT_ID = fc.constraint_object_id
INNER JOIN 
   sys.tables t 
      ON t.OBJECT_ID = fc.referenced_object_id
WHERE 
   f.parent_object_id = OBJECT_ID('Cars')
   
SELECT * FROM sys.foreign_keys 
SELECT * FROM sys.foreign_key_columns 
SELECT * FROM sys.tables 


SELECT 
COUNT(*)
FROM 
	sys.foreign_keys AS f
INNER JOIN 
	sys.foreign_key_columns AS fc 
		ON f.OBJECT_ID = fc.constraint_object_id
INNER JOIN 
	sys.tables t 
		ON t.OBJECT_ID = fc.referenced_object_id
WHERE 
	f.parent_object_id = OBJECT_ID('cars') AND COL_NAME(fc.parent_object_id,fc.parent_column_id) = 'model'
