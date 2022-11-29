-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Theft took place on July 28
-- Theft took place on Humphrey Street

--SELECT description
--FROM crime_scene_reports
--WHERE (month = 7 AND day = 28 AND street = "Humphrey Street");
----> 10:15AM @ Humphrey Street Backery / Littering took place at 16:36

--Earliest flight out of Fiftyville tomorrow
--origin airport id(8, Fiftyville) to destination airport id(4) / Flight id 36
--Destination = LGA, LaGuardia Airport, New York City

--Cars that left before 10:25AM
----> POTENTIAL THIEF: 5P2BI95(Vanessa), 94KL13X(Bruce), 6P58WS2(Barry), 4328GD8(Luca), G412CB7(Sofia), L93JTIZ(Iman), 322W7JE(Diana), 0NTHK55(Kelsey)

--ATM
----> Account number 28500762(Luca), 282968159(Kenny), 76054385(Taylor), 49610011(Bruce), 16153065(Brroke), 86363979(Kaelyn), 25506511(Iman), 81061156(Benista), 26013199(Diana)

--Current suspects: Bruce, Luca, Iman, Diana --> Passport number: 5773159633(Bruce), 8496433585(Luca), 7049073643(Iman), 3592750733(Diana)

--> FROM passengers table, Bruce and Luca are possible suspects

--> FROM phone_calls table, caller and receiver ---->  Bruce's phone number(367 555 5533) / Luca's phone number(389 555 5198)

--> Bruce is the thief.

--> Receiver is the accomplice, whose phone # is 375-555-8161

--> Accomlice is Robin