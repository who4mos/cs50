-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get description
SELECT *
FROM crime_scene_reports 
WHERE year = 2025 AND month = 7 AND day = 28
      AND description LIKE '%cs50%';
-- 10:15 am at Humphrey Street Bakery; 3 witnesses

-- View interviews
SELECT * FROM interviews
WHERE year = 2025 AND month = 7 AND day = 28;
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ...

-- Get plates (the thief was in some of those cars)
SELECT license_plate
FROM bakery_security_logs
WHERE year = 2025 AND month = 7 AND day = 28
AND hour = 10 AND minute >= 15 AND minute <= 25;

-- Get withdraws on theft day (thief owns some of these accounts)
SELECT account_number
FROM atm_transactions
WHERE year = 2025 AND month = 7 AND day = 28
      AND atm_location = 'Leggett Street'
      AND transaction_type = 'withdraw';

-- Get phone calls (with less than a minute) on theft day
SELECT caller, receiver
FROM phone_calls
WHERE year = 2025 AND month = 7 AND day = 28
      AND duration < 60;

-- Find earliest flight out of fiftyville (And destination)
SELECT f.id AS flight_id,
       a1.id AS origin_id, a1.full_name AS origin,
       a2.id AS destination_id, a2.full_name AS destination,
       a2.city AS destination_city
from flights f
JOIN airports a1 ON f.origin_airport_id = a1.id
JOIN airports a2 ON f.destination_airport_id = a2.id
WHERE year = 2025 AND month = 7 AND day = 29
      AND a1.city = 'Fiftyville'
ORDER BY hour, minute
LIMIT 1;
-- flight_id = 36; origin: fiftyville; destination: LaGuardia Airport
-- destination city: New York City

-- Get passengers' passports
SELECT *
FROM passengers
WHERE flight_id = 36;

-- Get thief
SELECT id, name
FROM people
JOIN bank_accounts ba ON people.id = ba.person_id
WHERE license_plate IN (
      SELECT license_plate
      FROM bakery_security_logs
      WHERE year = 2025 AND month = 7 AND day = 28
      AND hour = 10 AND minute >= 15 AND minute <= 25
) AND account_number IN (
      SELECT account_number
      FROM atm_transactions
      WHERE year = 2025 AND month = 7 AND day = 28
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
) AND phone_number IN (
      SELECT caller
      FROM phone_calls
      WHERE year = 2025 AND month = 7 AND day = 28
            AND duration < 60
) AND passport_number IN (
      SELECT passport_number
      FROM passengers
      WHERE flight_id = 36
);
-- Bruce

-- Get accomplice
SELECT name
FROM people
WHERE phone_number = (
      SELECT receiver
      FROM phone_calls
      WHERE year = 2025 AND month = 7 AND day = 28
            AND duration < 60
            AND caller = (
                SELECT phone_number
                FROM people
                WHERE id = 686048 -- Bruce's id
      )
);
-- Robin
