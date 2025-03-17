SELECT name
FROM people
WHERE id IN (
      SELECT person_id
      FROM stars
      WHERE movie_id IN (
      	    SELECT id
      	    FROM movies
      	    WHERE year = 2004
       )
);

-- )
-- ORDER BY birth;

-- Using JOIN
-- SELECT people.name
-- FROM people
-- JOIN stars ON people.id = stars.person_id
-- JOIN movies ON stars.movie_id = movies.id
-- WHERE movies.year = 2004
-- GROUP BY people.id
-- ORDER BY people.birth;
