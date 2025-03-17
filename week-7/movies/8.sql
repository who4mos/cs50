SELECT name
FROM people
WHERE id in (
      SELECT person_id
      FROM stars
      WHERE movie_id = (
      	    SELECT id
      	    FROM movies
      	    WHERE title = 'Toy Story'
      )
);

-- Using JOIN
-- SELECT people.name
-- FROM stars
-- JOIN movies ON stars.movie_id = movies.id
-- JOIN people ON stars.person_id = people.id
-- WHERE movies.title = 'Toy Story';
