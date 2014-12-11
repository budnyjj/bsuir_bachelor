CREATE TABLE awarded
(
	awarded_name         VARCHAR(255) NULL,
	awarded_post         VARCHAR(255) NULL,
	awarded_sex          CHAR NULL,
	awarded_rank         VARCHAR(255) NULL,
	awarded_job          VARCHAR(255) NULL,
	awarded_id           INTEGER NOT NULL
);

ALTER TABLE awarded
ADD PRIMARY KEY (awarded_id);

CREATE TABLE awards
(
	award_title          VARCHAR(255) NOT NULL,
	award_type           VARCHAR(20) NULL,
	award_description    VARCHAR(255) NULL,
	award_image_path     VARCHAR(255) NULL
);

ALTER TABLE awards
ADD PRIMARY KEY (award_title);

CREATE TABLE rewards_documents
(
	document_number      INTEGER NOT NULL,
	document_title       VARCHAR(255) NULL,
	document_date        DATE NULL
);

ALTER TABLE rewards_documents
ADD PRIMARY KEY (document_number);

CREATE TABLE fact_rewards
(
	award_title          VARCHAR(255) NOT NULL,
	awarded_basis        VARCHAR(255) NULL,
	document_number      INTEGER NOT NULL,
	reward_number        VARCHAR(20) NULL,
	awarded_id           INTEGER NOT NULL
);

ALTER TABLE fact_rewards
ADD PRIMARY KEY (document_number,award_title,awarded_id);

CREATE TABLE users
(
	user_login           VARCHAR(255) NOT NULL,
	user_pass            VARCHAR(255) NULL,
	user_email           VARCHAR(255) NULL
);

ALTER TABLE users
ADD PRIMARY KEY (user_login);

ALTER TABLE fact_rewards
ADD FOREIGN KEY R_3 (award_title) REFERENCES awards (award_title);

ALTER TABLE fact_rewards
ADD FOREIGN KEY R_4 (document_number) REFERENCES rewards_documents (document_number);

ALTER TABLE fact_rewards
ADD FOREIGN KEY R_7 (awarded_id) REFERENCES awarded (awarded_id);
