DROP DATABASE DummyDBLab5
GO
CREATE DATABASE DummyDBLab5
GO
USE DummyDBLab5
GO


CREATE TABLE Ta(
	aid INTEGER PRIMARY KEY,
	a2 INTEGER UNIQUE,
	a3 NVARCHAR(100)
)

CREATE TABLE Tb(
	bid INTEGER PRIMARY KEY,
	b2 INTEGER,
	b3 DATE
)

CREATE TABLE Tc(
	cid INTEGER PRIMARY KEY,
	aid INTEGER,
	bid INTEGER,
	c2 INTEGER,
	CONSTRAINT FK_Tc_Ta FOREIGN KEY (aid) REFERENCES Ta(aid),
	CONSTRAINT FK_Tc_Tb FOREIGN KEY (bid) REFERENCES Tb(bid)
)
GO

INSERT INTO Ta(aid,a2, a3) 
VALUES (1, 2, 'oare')
INSERT INTO Ta(aid,a2, a3) 
VALUES (2, 24, 'asdf')
INSERT INTO Ta(aid,a2, a3) 
VALUES (6, 222, 'nu stiui')
INSERT INTO Ta(aid,a2, a3) 
VALUES (13, 54, 'papa')
INSERT INTO Ta(aid,a2, a3) 
VALUES (14, 123, 'care')
INSERT INTO Ta(aid,a2, a3) 
VALUES (15, 4, 'mancare')
INSERT INTO Ta(aid,a2, a3) 
VALUES (31, 52, 'iubire')
INSERT INTO Ta(aid,a2, a3) 
VALUES (51, 23, 'ura')
GO


-- a

-- clustered index scan
SELECT * FROM Ta

-- clustered index seek
SELECT * FROM Ta a WHERE a.aid = 2 

-- nonclustered index scan
SELECT a.a2 FROM Ta a 

-- nonclustered index seek
SELECT a.a2 FROM Ta a where a.a2 > 10

-- key lookup
SELECT a.a2, a.a3 from Ta a where a.a2 = 222



-- b

-- inserting into Tb
SELECT * FROM Tb

INSERT INTO Tb(bid, b2, b3)
VALUES (1, 13, '20020503')
INSERT INTO Tb(bid, b2, b3)
VALUES (14, 2, '20320503')
INSERT INTO Tb(bid, b2, b3)
VALUES (4, 2, '20020513')
INSERT INTO Tb(bid, b2, b3)
VALUES (124, 4, '20320203')
INSERT INTO Tb(bid, b2, b3)
VALUES (23,432, '20120402')
INSERT INTO Tb(bid, b2, b3)
VALUES (45, 432, '20010406')
INSERT INTO Tb(bid, b2, b3)
VALUES (3, 2, '20211003')
INSERT INTO Tb(bid, b2, b3)
VALUES (6, 132, '20220202')
INSERT INTO Tb(bid, b2, b3)
VALUES (432, 123, '20220202')
INSERT INTO Tb(bid, b2, b3)
VALUES (222, 342, '20220303')


-- withtout a nonclusterd index 

SELECT * FROM Tb b WHERE b.b2 = 2

-- number of rows read: 10, actual number of rows: 3
-- estimated cpu cost = 0.000168

-- creating the non clustered index
CREATE INDEX IX_Tb_b2 ON Tb(b2) INCLUDE (b3)

DROP INDEX IX_Tb_b2 ON Tb

SELECT * FROM Tb b WHERE b.b2 = 2
--number of rows read = 3, actual number of rows= 3
-- estimated cpu cost 0.0001603


-- c

-- inserting data in Tc

SELECT * FROM Ta
SELECT * FROM Tb

INSERT INTO Tc(cid, aid, bid, c2)
VALUES (1, 2, 23, 123)
INSERT INTO Tc(cid, aid, bid, c2)
VALUES (432, 6, 3, 65)
INSERT INTO Tc(cid, aid, bid, c2)
VALUES (12, 15, 222, 345)
INSERT INTO Tc(cid, aid, bid, c2)
VALUES (3, 13, 45, 654)
INSERT INTO Tc(cid, aid, bid, c2)
VALUES (154, 51, 6, 324)
INSERT INTO Tc(cid, aid, bid, c2)
VALUES (333, 2, 1, 432)
INSERT INTO Tc(cid, aid, bid, c2)
VALUES (14, 6, 1, 32)
INSERT INTO Tc(cid, aid, bid, c2)
VALUES (32, 51, 124, 54)
INSERT INTO Tc(cid, aid, bid, c2)
VALUES (543, 15, 222, 654)
INSERT INTO Tc(cid, aid, bid, c2)
VALUES (142, 2, 23, 3244)

SELECT * FROM Tc
GO

CREATE VIEW v_Get_Ta_a3_Tb_b2_On_Tc AS
	SELECT a.a3, b.b3 FROM Ta a
	INNER JOIN Tc c ON c.aid = a.aid
	INNER JOIN Tb b ON c.bid = b.bid
	WHERE a.a3 = 'ura'
GO
 
DROP VIEW v_Get_Ta_a3_Tb_b2_On_Tc

SELECT * FROM v_Get_Ta_a3_Tb_b2_On_Tc

-- clustered index scan/seek everywhere

CREATE INDEX IX_Ta_a3 ON Ta(a3)
DROP INDEX IX_Ta_a3 on Ta

-- now it uses the new index
