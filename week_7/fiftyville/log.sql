-- Keep a log of any SQL queries you execute as you solve the mystery.

-- First, we are going to look at the reports from that day, and also from the place of the robbery
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';

-- One of the crime scene reports from the previous query says that the robbery took place at the Humphrey Street's bakery at 10:15 A.M., and that there were three witnesses. We will look at the interviews (on the day of the robbery) to gather more information from the witnesses' stories
SELECT * FROM interviews WHERE month = 7 AND day= 28;

-- One of the transcripts says that the witness saw the thief leaving the bakery parking lot within 10 minutes of the theft (so around 10:25 A.M.), so we will check the bakery's security log at that time frame.
SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <25;

-- Another transcript states that a witness saw the thief withdrawing money from an ATM earlier that morning, so we will look at the ATM transactions on that time frame
SELECT * FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- Finally, the last transcript says that the thief had a phone call lasting less than a minute, telling someone to book the earliest flight out of Fiftyville for the next day. We are then, firstly going to look at the phone_calls with that time limit.
SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60;


-- Now we should look for the earliest flight from Fiftyville the day after the robbery, so on July 29. This time we have an unequivocal result, as there is only one "earliest flight" (id = 36). We'll make sure that the origin_airport_id corresponds to Fiftyville by joining the table with the airports one.
SELECT * FROM flights JOIN airports ON flights.origin_airport_id = airports.id WHERE month = 7 AND day = 29 ORDER BY hour;

-- We can now look at the passengers from that flight:
SELECT * FROM passengers WHERE flight_id = 36;

-- With all the previous information, we will begin making more complex searchs, adding filters based on the information we have, to keep reducing the suspects. We can join the passenger's table, with the people's one to get the data of the passengers of the earliest flight that we selected earlier. And then we can also join it with the results from the query of the bakery's parking lot. This narrows it down to 4 suspects (we have to remember we are looking for both the thief and the accomplice)

SELECT * FROM passengers JOIN people ON passengers.passport_number = people.passport_number WHERE passengers.flight_id = 36 AND people.license_plate IN (
    SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <25
    )
;

-- Now we can filter the results for the people that flew in the earliest flight of the 29th, that also left the bakery within 10 minutes of the robbery, based on the phone call records, to know which one of them made a call that lasted less than a minute on the 28th. We have now 3 thief suspects.

SELECT * FROM passengers JOIN people ON passengers.passport_number = people.passport_number WHERE passengers.flight_id = 36 AND people.license_plate IN (
    SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <25
    ) AND people.phone_number IN (
        SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60
        )
;

-- Finally, we can use the ATM information, to get the information of the person that meets all of the previous criteria, and also withdrew money on the 28th of july. That returns a single record, meaning we have identified our thief.

SELECT id, name, phone_number, license_plate, passport_number FROM passengers JOIN people ON passengers.passport_number = people.passport_number JOIN bank_accounts ON bank_accounts.person_id = people.id WHERE passengers.flight_id = 36 AND people.license_plate IN (
    SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <25
    ) AND people.phone_number IN (
        SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60
        ) AND account_number IN (
            SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
            )
;

-- Now, to find the accomplice, we can use the thief's phone number to track the receiver of the call that he made, which lasted less than a minute, and was made on the day of the robbery. We will join this with the people's table to get the data from the accomplice. This returns a single record: our accomplice.

SELECT people.id, name, phone_number, license_plate, passport_number FROM phone_calls JOIN people ON people.phone_number = phone_calls.receiver WHERE month = 7 AND day = 28 AND duration < 60 and caller = '(367) 555-5533';

-- To conclude our investigation, we have to determine which city Bruce and Robin flew to. Having the id of the flight should make this easy for us. This query returns the airport of LaGuardia (NYC)
SELECT * FROM flights JOIN airports ON flights.destination_airport_id = airports.id WHERE month = 7 AND day = 29 AND flights.id = 36;
