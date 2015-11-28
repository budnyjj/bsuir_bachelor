CREATE TABLE award_documents
(
	formal_number        TEXT NOT NULL,
	title                TEXT NOT NULL,
	date                 DATE NOT NULL,
	id                   INTEGER UNSIGNED primary key NOT NULL AUTO_INCREMENT
);

CREATE TABLE award_fact
(
	basis                TEXT NOT NULL,
	formal_number        TEXT NOT NULL,
	id_document          INTEGER UNSIGNED NOT NULL,
	id_award             INTEGER UNSIGNED NOT NULL,
	id_awarded           INTEGER UNSIGNED NOT NULL
);

ALTER TABLE award_fact
ADD PRIMARY KEY (id_document,id_award,id_awarded);

CREATE TABLE awarded
(
	id                   INTEGER UNSIGNED primary key NOT NULL AUTO_INCREMENT,
	name                 TEXT NOT NULL,
	sex                  CHAR NOT NULL,
	job                  TEXT NOT NULL,
	post                 TEXT NOT NULL,
	rank                 TEXT NOT NULL
);

CREATE TABLE awards
(
	title                TEXT NOT NULL,
	type                 TEXT NOT NULL,
	description          TEXT NOT NULL,
	image_path           TEXT NOT NULL,
	id                   INTEGER UNSIGNED primary key NOT NULL AUTO_INCREMENT
);

ALTER TABLE award_fact
ADD CONSTRAINT R_6 FOREIGN KEY (id_document) REFERENCES award_documents (id);

ALTER TABLE award_fact
ADD CONSTRAINT R_9 FOREIGN KEY (id_award) REFERENCES awards (id);

ALTER TABLE award_fact
ADD CONSTRAINT R_10 FOREIGN KEY (id_awarded) REFERENCES awarded (id);
