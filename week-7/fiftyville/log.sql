-- Find report (10:15 am | Humprey Street bakery | tree witnesses)
SELECT id, street, description
FROM crime_scene_reports
WHERE year = 2024 AND month = 7 AND day = 28;

-- Find interviews
SELECT id, name, transcript
FROM interviews 
WHERE year = 2024 AND month = 7 AND day = 28
AND transcript LIKE '%bakery%';

-- Check Ruth's interview (Thief owns one of these cars)
SELECT license_plate
FROM bakery_security_logs
WHERE activity = 'exit'
AND year = 2024 AND month = 7 AND day = 28
AND hour = 10
AND minute > 15 AND minute <= 25;

-- Check Eugene's interview (Thief owns some of these accounts)
SELECT account_number
FROM atm_transactions 
WHERE year = 2024 AND month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- Check Raymond's interview (Thief owns some of these caller numbers)
SELECT caller
FROM phone_calls
WHERE year = 2024 AND month = 7 AND day = 28
AND duration < 60;

-- Find earliest flight out of fiftyville the day after the theft
-- Then find all passengers on that flight
-- (One of these passport numbers is from our thief)
SELECT passport_number
FROM passengers
WHERE flight_id = (
      SELECT id
      FROM flights
      WHERE year = 2024 AND month = 7 AND day = 29
      AND origin_airport_id = (
      	  SELECT id
    	  FROM airports 
    	  WHERE city = 'Fiftyville'
      )
      ORDER BY hour, minute
      LIMIT 1
);

-- Thief's name
SELECT name
FROM people
WHERE license_plate IN (
      SELECT license_plate
      FROM bakery_security_logs
      WHERE activity = 'exit'
      AND year = 2024 AND month = 7 AND day = 28
      AND hour = 10
      AND minute > 15 AND minute <= 25
) AND id IN (
      SELECT person_id
      FROM bank_accounts
      WHERE account_number IN (
      	    SELECT account_number
      	    FROM atm_transactions 
	    WHERE year = 2024 AND month = 7 AND day = 28
	    AND atm_location = 'Leggett Street'
	    AND transaction_type = 'withdraw' 
      )
) AND phone_number IN (
      SELECT caller
      FROM phone_calls
      WHERE year = 2024 AND month = 7 AND day = 28
      AND duration < 60 
) AND passport_number IN (
      SELECT passport_number
      FROM passengers
      WHERE flight_id = (
      	    SELECT id
      	    FROM flights
      	    WHERE year = 2024 AND month = 7 AND day = 29
      	    AND origin_airport_id = (
      	    	SELECT id
    	  	FROM airports 
    	  	WHERE city = 'Fiftyville'
      	    )
      	    ORDER BY hour, minute
      	    LIMIT 1
  p    )
);

-- City that the thief escaped to 
SELECT city
FROM airports
WHERE id = (
      SELECT destination_airport_id
      FROM flights
      WHERE year = 2024 AND month = 7 AND day = 29
      AND origin_airport_id = (
          SELECT id
	  FROM airports 
	  WHERE city = 'Fiftyville'
      )
      ORDER BY hour, minute
      LIMIT 1
);

-- Accomplice
SELECT name
FROM people
WHERE phone_number = (
      SELECT receiver
      FROM phone_calls
      WHERE year = 2024 AND month = 7 AND day = 28
      AND duration < 60
      AND caller = (
      	  SELECT phone_number
	  FROM people
	  WHERE license_plate IN (
	  	SELECT license_plate
		FROM bakery_security_logs
		WHERE activity = 'exit'
      		AND year = 2024 AND month = 7 AND day = 28
      		AND hour = 10
      		AND minute > 15 AND minute <= 25
          ) AND id IN (
      	    	SELECT person_id
      	      	FROM bank_accounts
      	      	WHERE account_number IN (
      	      	      SELECT account_number
      	    	      FROM atm_transactions 
	    	      WHERE year = 2024 AND month = 7 AND day = 28
	    	      AND atm_location = 'Leggett Street'
	    	      AND transaction_type = 'withdraw' 
      	        ) AND phone_number IN (
      	      	      SELECT caller
      		      FROM phone_calls
      		      WHERE year = 2024 AND month = 7 AND day = 28
      		      AND duration < 60 
                ) AND passport_number IN (
      	      	      SELECT passport_number
      		      FROM passengers
      		      WHERE flight_id = (
      	    	      	    SELECT id
      	    		    FROM flights
      	    		    WHERE year = 2024 AND month = 7 AND day = 29
      	    		    AND origin_airport_id = (
      	    		    	SELECT id
    	  		      	FROM airports 
    	  		      	WHERE city = 'Fiftyville'
      	    		    )
      	            	    ORDER BY hour, minute
      	    	    	    LIMIT 1
      		      )
	        )
	  )
      )
);
