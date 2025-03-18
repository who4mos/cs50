CREATE TABLE IF NOT EXISTS students (
       id INTEGER,
       name TEXT,
       PRIMARY KEY(id)
);

CREATE TABLE IF NOT EXISTS houses (
       id INTEGER,
       name TEXT UNIQUE,
       head TEXT,
       PRIMARY KEY(id)
);

CREATE TABLE IF NOT EXISTS house_assignments (
       student_id INTEGER UNIQUE,
       house_id INTEGER,
       FOREIGN KEY(student_id) REFERENCES students(id),
       FOREIGN KEY(house_id) REFERENCES houses(id)
);
