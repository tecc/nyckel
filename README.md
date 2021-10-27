# Nyckel Password Manager

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

## Licence

Nyckel is licensed under the MIT License.
The full licence text can be viewed in [LICENCE.txt](./LICENCE.txt).