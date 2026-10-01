CREATE TABLE IF NOT EXISTS users (
  email VARCHAR PRIMARY KEY,                                -- User's email
  user_name VARCHAR NOT NULL,                               -- User's name
  password VARCHAR NOT NULL,                               -- User's hashed password
  avatar VARCHAR NOT NULL,
  admin INTEGER NOT NULL                                    -- Admin -> 1 | StdUser -> 0
);

CREATE TABLE IF NOT EXISTS authors (
  author_name VARCHAR PRIMARY KEY                           -- Author name
);
CREATE TABLE IF NOT EXISTS documents (
  title VARCHAR,                                            -- Document title
  author_name VARCHAR NOT NULL,                             -- Author name
  user_owner VARCHAR NOT NULL,                              -- User that creates the file
  term_frequency VARCHAR NOT NULL,                          -- JSON with tf Data
  term_positions VARCHAR NOT NULL,                          -- JSON with word - positions
  content VARCHAR NOT NULL,
  cover VARCHAR NOT NULL,
  rating REAL NOT NULL,
  PRIMARY KEY(title, author_name),
  FOREIGN KEY(author_name) REFERENCES authors(author_name),
  FOREIGN KEY(user_owner) REFERENCES users(email)
);

CREATE TABLE IF NOT EXISTS favourites (
  title VARCHAR NOT NULL,
  author_name VARCHAR NOT NULL,
  user_email VARCHAR NOT NULL,
  PRIMARY KEY(title, author_name, user_email),
  FOREIGN KEY(title, author_name) REFERENCES documents(title, author_name),
  FOREIGN KEY(user_email) REFERENCES users(email)
);

CREATE TABLE IF NOT EXISTS ratings (
  user_email VARCHAR NOT NULL,
  title VARCHAR NOT NULL,
  author_name VARCHAR NOT NULL,
  points NUMERIC NOT NULL,
  PRIMARY KEY(user_email, title, author_name),
  FOREIGN KEY(title, author_name) REFERENCES documents(title, author_name),
  FOREIGN KEY(user_email) REFERENCES users(email)
);