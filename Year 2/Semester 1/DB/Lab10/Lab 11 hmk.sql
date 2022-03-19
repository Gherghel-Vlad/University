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
GO

DROP PROCEDURE usp_RunTest
GO

CREATE PROCEDURE usp_RunTest(@TestName NVARCHAR(50))
AS
	-- getting the id of the test with the given name
	DECLARE @TestIDNr INT
	SELECT @TestIDNr=T.TestID FROM Tests T WHERE T.Name = @TestName
	
	-- creating a new entry in TestRuns so i have the TestRunID to work with
	DECLARE @TestRunIDNr INT
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES (NULL, NULL, NULL)
	SELECT @TestRunIDNr = SCOPE_IDENTITY()

	PRINT( 'The test ' + @TestName + ' with id ' + CAST(@TestIDNr AS NVARCHAR) + ' has received the TestRun entry with value ' + CAST(@TestRunIDNr AS NVARCHAR))


	-- declaring the variables i will use in the view testing
	DECLARE @ViewIDNr INT
	DECLARE @ViewName NVARCHAR(50)
	DECLARE @StartAtVar DATETIME
	DECLARE @EndAtVar DATETIME

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
		SELECT @ViewName = [V.Name] FROM [Views] V WHERE [V.ViewID] = [@ViewIDNr]

		-- StartAt
		SELECT @StartAtVar=GETDATE()

		--executing the view
		SELECT * From @ViewName

		--EndAt
		SELECT @EndAtVar=GETDATE()

		-- Inserting the data gathered
		INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) 
		VALUES(@TestRunIDNr, @ViewIDNr, @StartAtVar, @EndAtVar)

		-- printing beautiful message
		PRINT('Test on the view ' + @ViewName + ' with id ' + CAST(@ViewIDNr AS NVARCHAR) + ' ran from ' + CAST(@StartAtVar AS NVARCHAR) + ' until ' + CAST(@EndAtVar AS NVARCHAR) )

		-- fetch the next record from the cursor
		FETCH NEXT FROM db_cursor_view INTO @ViewIDNr

	END
	 
	 -- REMINDER: DONT FORGET TO TEST THE VIEW CURSOR PART BEFORE CONTINUING!!!!!



GO

EXEC usp_RunTest 'Test1'
GO


