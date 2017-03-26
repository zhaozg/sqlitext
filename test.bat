@echo off

build\sqlite build\safe.db < sql\enc_1.sql
if %errorlevel% EQU 0  echo 1. Pass create and encrypt

build\sqlite build\safe1.db < sql\enc_2.sql
if %errorlevel% EQU 0  echo 2. Pass create and encrypt (X'hex')

build\sqlite build\safe.db < sql\convert.sql
if %errorlevel% EQU 0  echo 3. Pass convert key

build\sqlite build\safe.db < sql\ok.sql
if %errorlevel% EQU 0  echo 4. Pass open and decrypt after changekey

build\sqlite build\safe.db < sql\error.sql
if %errorlevel% EQU 1  echo 5. Pass, must fail to open and decrypt use oldkey after changekey

del build\safe.db build\safe1.db