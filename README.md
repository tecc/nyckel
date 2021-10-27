# Nyckel Password Manager

**Disclaimer: This project was *not* made or inspected by a security expert. Use with caution.**



Nyckel Password Manager (or just Nyckel) is a simple password manager.
It is decentralised, with the possibility to synchronise between devices using a server.

> The name, "Nyckel", is Swedish for "key".

## Structure

Each instance of NyckelD has **keyrings**. Each instance also has a **salt**.

Keyrings are containers for **passwords**. Keyrings have unique IDs, and by extension, unique **master keys**.

Master keys are generated through a combination of the instance salt, the keyrings ID, and a **master password**.

Master passwords are decided by the user, and are the essential keys to unlocking all the keyrings.

A keyring's password is encrypted and decrypted using the master key. The actual password is however not used as the encrypted data; instead, the data is offset by the keyring's password ID.

> More is yet to be described.

## Project structure

Nyckel is split into several projects to make maintenance easier.

- libNyckel
  
  > The base library.
- NyckelD
  
  > A daemon that handles storage, synchronisation, etc. 
  > for one device.
  + NyckelS
    
    > Server-side software for synchronising across
    > devices.

## Design goals

The design is based around security and simplicity, namely:

1. Avoiding storing or transmitting important information unsecurely (e.g. raw passwords in memory should be discarded as fast as possible).

2. Making everything as unique as possible, even given the same input (e.g. if 2 passwords are the same, they shouldn't produce the same encrypted output).

3. Keeping everything independent from one another (e.g. an instance of NyckelD should not depend on an instance of NyckelS, should it be inaccessible).

## Licence

Nyckel is licensed under the MIT License.
The full licence text can be viewed in [LICENCE.txt](./LICENCE.txt).