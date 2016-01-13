@echo off

sqlite safe.db < enc_ok.sql
if %errorlevel% EQU 0  echo 1. Pass create and encrypt
sqlite safe.db < dec_ok.sql
if %errorlevel% EQU 0  echo 2. Pass open and decrypt
sqlite safe.db < convert.sql
if %errorlevel% EQU 0  echo 3. Pass convert key
sqlite safe.db < ok.sql
if %errorlevel% EQU 0  echo 4. Pass open and decrypt after changekey
sqlite safe.db < error.sql
if %errorlevel% EQU 1  echo 5. Pass, must fail to open and decrypt use oldkey after changekey
del safe.db
