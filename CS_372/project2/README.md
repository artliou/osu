# CS 372 - Project 2
## Jeremy Prater

# Server compilation

```bash
cd server
./start_build
```

If the file is not executable, please run.

```bash
chmod +x ./start_build
```

# Server execution (on flip1)

```bash
cd server
./ftserver [serverport]
```

Example

```bash
./ftserver 12345
```

# Client execution (on flip2)

```bash
cd client
./ftclient flip1 12345 -l 4567
./ftclient flip1 12345 -g somefile.txt 4567
```

If the file is not executable, please run.

```bash
chmod +x ./ftclient
```

