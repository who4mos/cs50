UPDATE shows
SET title = 'Adventure Time'
WHERE title LIKE 'adventure time'; 

UPDATE shows
SET title = 'Arrow'
WHERE title LIKE 'arrow';

UPDATE shows
SET title = 'Avatar: The Last Airbender'
WHERE title LIKE 'avatar%';

UPDATE shows
SET title = 'Brooklyn Nine-Nine'
WHERE title LIKE 'b%99';

UPDATE shows
SET title = 'Community'
WHERE title LIKE 'community';

UPDATE shows
SET title = 'Family Guy'
WHERE title LIKE 'family guy';

UPDATE shows
SET title = 'Friends'
WHERE title LIKE 'friends';

UPDATE shows
SET title = 'Game of Thrones'
WHERE title LIKE 'game of thrones'
OR title LIKE 'got';

UPDATE shows
SET title = 'Gilmore Girls'
WHERE title LIKE 'gilmore girls';

UPDATE shows
SET title = 'Grey''s Anatomy'
WHERE title LIKE 'grey%s anatomy';

UPDATE shows
SET title = 'How I Met Your Mother'
WHERE title LIKE 'how i met your mother';

UPDATE shows
SET title = 'It''s Always Sunny in Philadelphia'
WHERE title LIKE 'it%s always sunny in phil%';

UPDATE shows
SET title = 'Parks And Recreation'
WHERE title LIKE 'parks and %';

UPDATE shows
SET title = 'Sherlock'
WHERE title LIKE 'sherlock%';

UPDATE shows
SET title = 'Squid Game'
WHERE title LIKE 'squid game';

UPDATE shows
SET title = 'The Bachelorette'
WHERE title LIKE 'the bachelorette';

UPDATE shows
SET title = 'The Crown'
WHERE title LIKE 'the crown';

UPDATE shows
SET title = 'The Office'
WHERE title LIKE '%office';

UPDATE shows
SET title = 'The Queen''s Gambit'
WHERE title LIKE '%queen%gambit';

UPDATE shows
SET title = 'The Untamed'
WHERE title LIKE 'the untamed';

-- After listing all shows alphabetically its visible that billions and criminal minds
-- still need fix

UPDATE shows
SET title = 'Billions'
WHERE title LIKE 'billions';

UPDATE shows
SET title = 'Criminal Minds'
WHERE title LIKE 'criminal minds';

-- Now we can list

SELECT * FROM shows ORDER BY title;
