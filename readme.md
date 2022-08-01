# MONITORING
*A simple web service monitoring application*
# Description
This project is a web monitoring program written in C to get status from three protocols: PING, HTTP and DNS. The information acquired is stored in monitoring.log file inside the programs folder and a simplify version is printed in the terminal.

# Usage
## Requirements


Monitoring requires a gcc compiler, standard C libraries and it runs only in linux system (only ubuntu was tested).

## Install

Run `make` comamnd in the repository folder:

	$> make

Make supports the following commands:

> - `make` - compile the project;
> - `make clog` - remove log file
> - `make clean` - remove all objects (`.o`) files;
> - `make fclean` - perform clean and also remove its dependencies and executable file;
> - `make re` - recompile project.

## Configuration

Monitoring reads the instructions in the **monitoring.db** file located in the repository folder, which must be formatted as follows:

| Protocolo  |  Configurations |
| :-----: | --------- |
| PING | name, protocol, address, interval |
| DNS | name, protocol, address, interval, dns server |
| HTTP | name, protocol, address, http method, expected http code, interval | 

Each service must be separated by lines and the configuration by coloumns separated by tab, as shown below:

```
 # monitoring.db

teste ping	PING	example.com	5
teste dns	DNS	example.com	10	8.8.8.8
teste http	HTTP	example.com	GET	200	30
```

## Run

Just excecute in the command line:

	$>./monitoring

If you want to recover the simplified output from previous monitoring execution, run with the flag `--simplify`

	$>./monitoring --simplify


# Support

If you have any trouble or find any issues send me an e-mail: pe.pn03@gmail.com
