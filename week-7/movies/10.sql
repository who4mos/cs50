SELECT name
FROM people
WHERE id IN (
      SELECT person_id
      FROM directors
      WHERE movie_id IN (
      	    SELECT movie_id
	    FROM ratings
	    WHERE rating >= 9
      )
);

-- Using JOIN
-- SELECT people.name
-- FROM directors
-- JOIN people ON directors.person_id = people.id
-- JOIN movies ON directors.movie_id = movies.id
-- JOIN ratings ON movies.id = ratings.movie_id
-- WHERE ratings.rating >= 9.0
-- GROUP BY people.id;
