USE MovieShowsDBv2
GO


-- modify a column 
-- transforms the name column from NVARCHAR to CHAR and back

CREATE PROCEDURE usp_AlterUsersColumnNameToChar AS
	ALTER TABLE Users 
	ALTER COLUMN name CHAR(100) NOT NULL
GO

CREATE PROCEDURE usp_AlterUsersColumnNameToNVarChar AS
	ALTER TABLE Users 
	ALTER COLUMN name NVARCHAR(100) NOT NULL
GO

DROP PROCEDURE usp_AlterUsersColumnNameToChar
GO

SELECT * FROM Users
GO

EXEC usp_AlterUsersColumnNameToChar
EXEC usp_AlterUsersColumnNameToNVarChar
GO


-- add/ remove a column
-- adding/removing the column date_of_birth to the table Users

CREATE PROCEDURE usp_AlterUsersAddColumnDateOfBirth AS
	ALTER TABLE Users
	ADD date_of_birth DATE NULL  

GO

EXEC usp_AlterUsersAddColumnDateOfBirth
GO

CREATE PROCEDURE usp_AlterUsersDropColumnDateOfBirth AS
	ALTER TABLE Users
	DROP COLUMN date_of_birth
GO

EXEC usp_AlterUsersDropColumnDateOfBirth
GO

-- add /remove a DEFAULT constraint
-- adding/removing a default description on the Users table

CREATE PROCEDURE usp_AlterUsersAddConstraintDefaultDescription AS
	ALTER TABLE Users
	ADD CONSTRAINT df_description
	DEFAULT 'Hello world!' FOR description;
GO

EXEC usp_AlterUsersAddConstraintDefaultDescription
GO



CREATE PROCEDURE usp_AlterUsersDropConstraintDefaultDescription AS
	ALTER TABLE Users
	DROP CONSTRAINT df_description
GO

EXEC usp_AlterUsersDropConstraintDefaultDescription
GO

-- add / remove a primary key
-- add / remove the constraint that makes (user_id ,review_id) as primary key in UserReviewLikes



CREATE PROCEDURE usp_AlterUserReviewLikesAddConstraintPrimaryKey AS
	ALTER TABLE UserReviewLikes
	ADD CONSTRAINT pk_UserIdReviewId
	PRIMARY KEY(user_id, review_id)
GO

EXEC usp_AlterUserReviewLikesAddConstraintPrimaryKey
GO

CREATE PROCEDURE usp_AlterUserReviewLikesDropConstraintPrimaryKey AS
	ALTER TABLE UserReviewLikes
	DROP CONSTRAINT pk_UserIdReviewId;
GO


EXEC usp_AlterUserReviewLikesDropConstraintPrimaryKey
GO


-- add / remove a candidate key
CREATE PROCEDURE usp_AlterUsersAddConstraintUniqueEmail AS
	ALTER TABLE Users
	ADD CONSTRAINT uq_Email
	UNIQUE (email)
GO

EXEC usp_AlterUsersAddConstraintUniqueEmail
GO

CREATE PROCEDURE usp_AlterUsersDropConstraintUniqueEmail AS
	ALTER TABLE Users
	DROP CONSTRAINT uq_Email
GO


EXEC usp_AlterUsersDropConstraintUniqueEmail
GO

-- add remove a foregin key
-- removing/adding the foreign key constraint from UserReviewLikes table on column review_id

CREATE PROCEDURE usp_AlterUserReviewLikesDropConstraintForeignKeyReviewId
AS
	ALTER TABLE UserReviewLikes
	DROP CONSTRAINT FK_UserReviewLikes_Reviews

GO


CREATE PROCEDURE usp_AlterUserReviewLikesAddConstraintForeignKeyReviewId
AS
	ALTER TABLE UserReviewLikes
	ADD CONSTRAINT FK_UserReviewLikes_Reviews FOREIGN KEY (review_id) REFERENCES Reviews(review_id)
GO

EXEC usp_AlterUserReviewLikesDropConstraintForeignKeyReviewId
GO

EXEC usp_AlterUserReviewLikesAddConstraintForeignKeyReviewId
GO



-- create / drop a table

CREATE PROCEDURE usp_CreateTableFriends AS
	CREATE TABLE Friends(
	user_id INT NOT NULL,
	friend_id INT NOT NULL
	CONSTRAINT FK_Friends_User_ID FOREIGN KEY (user_id) REFERENCES Users(user_id),
	CONSTRAINT FK_Friends_Friend_ID FOREIGN KEY (friend_id) REFERENCES Users(user_id)
	)
GO

EXEC usp_CreateTableFriends
GO

CREATE PROCEDURE usp_DropTableFriends AS
	DROP TABLE Friends
GO

EXEC usp_DropTableFriends
GO

-- creating the version table

CREATE TABLE DBVersion(
	Lock VARCHAR(20) NOT NULL DEFAULT 'One row table',
	CurrentVersionNumber INT NOT NULL,
	CONSTRAINT PK_Version_Lock PRIMARY KEY (Lock),
	CONSTRAINT CK_Version_Locked CHECK (LOCK='One row table')
)
GO

DROP TABLE DBVersion
GO


INSERT INTO DBVersion(CurrentVersionNumber) VALUES (1)
GO

SELECT * FROM DBVersion
GO

-- creating the version table
CREATE TABLE VersionProcedures(
	VersionNumber INT PRIMARY KEY NOT NULL,
	Up NVARCHAR(200),
	Down NVARCHAR(200)
)
GO

SELECT * FROM VersionProcedures

INSERT INTO VersionProcedures(VersionNumber, Up, Down) 
VALUES (1, 'usp_AlterUsersColumnNameToChar', NULL)
INSERT INTO VersionProcedures(VersionNumber, Up, Down) 
VALUES (2, 'usp_AlterUsersAddColumnDateOfBirth', 'usp_AlterUsersColumnNameToNVarChar')
INSERT INTO VersionProcedures(VersionNumber, Up, Down) 
VALUES (3, 'usp_AlterUsersAddConstraintDefaultDescription', 'usp_AlterUsersDropColumnDateOfBirth')
INSERT INTO VersionProcedures(VersionNumber, Up, Down) 
VALUES (4, 'usp_AlterUserReviewLikesAddConstraintPrimaryKey', 'usp_AlterUsersDropConstraintDefaultDescription')
INSERT INTO VersionProcedures(VersionNumber, Up, Down) 
VALUES (5, 'usp_AlterUsersAddConstraintUniqueEmail', 'usp_AlterUserReviewLikesDropConstraintPrimaryKey')
INSERT INTO VersionProcedures(VersionNumber, Up, Down) 
VALUES (6, 'usp_AlterUserReviewLikesDropConstraintForeignKeyReviewId', 'usp_AlterUsersDropConstraintUniqueEmail')
INSERT INTO VersionProcedures(VersionNumber, Up, Down) 
VALUES (7, 'usp_CreateTableFriends', 'usp_AlterUserReviewLikesAddConstraintForeignKeyReviewId')
INSERT INTO VersionProcedures(VersionNumber, Up, Down) 
VALUES (8, NULL, 'usp_DropTableFriends')



GO

CREATE PROCEDURE usp_UpdateDBToVersion(@NewVersion INT)
AS
BEGIN

	DECLARE @CurVersion INT
	DECLARE @StrProdName NVARCHAR(200)
	SELECT @CurVersion=CurrentVersionNumber FROM DBVersion

	WHILE(@NewVersion != @CurVersion)
		BEGIN
		IF @NewVersion > @CurVersion
			BEGIN
			
			PRINT 'Going up from version ' + CAST(@CurVersion AS VARCHAR)

			SELECT @StrProdName=Up FROM VersionProcedures WHERE VersionNumber=@CurVersion

			IF @StrProdName is NULL
				BEGIN
				PRINT 'No more versions.'
				BREAK
				END

			EXEC (@StrProdName)
			SET @CurVersion = @CurVersion + 1

			END
		ELSE
			BEGIN

			PRINT 'Going down from version ' + CAST(@CurVersion AS VARCHAR)
			SELECT @StrProdName=Down FROM VersionProcedures WHERE VersionNumber=@CurVersion

			IF @StrProdName is NULL
				BEGIN
				PRINT 'No more versions.'
				BREAK
				END

			EXEC (@StrProdName)
			SET @CurVersion = @CurVersion - 1

			END
		END
	PRINT 'Updating Database version..'
	UPDATE DBVersion SET CurrentVersionNumber = @CurVersion
	PRINT 'Current DB Version: ' + CAST(@CurVersion AS VARCHAR)
	PRINT 'Done!'

END
GO

DROP PROCEDURE usp_UpdateDBToVersion
GO

SELECT Down FROM VersionProcedures WHERE VersionNumber=10

EXEC usp_UpdateDBToVersion 1
GO

SELECT * FROM DBVersion
GO







