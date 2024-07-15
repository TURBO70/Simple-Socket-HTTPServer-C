## Description:
<p id="description">This project implements a basic HTTP server in C using sockets to handle GET and POST requests. It listens on a specified port (8080 by default) and responds to client requests accordingly.</p>

## Dependencies
* This project utilizes standard C libraries (stdio.h, stdlib.h, string.h, unistd.h, sys/socket.h, netinet/in.h) and assumes availability of POSIX sockets for networking.


<h2>Features</h2>

* GET Requests: Supports handling of GET requests for root (/) and /index.html paths.


* POST Requests: Echoes back received POST data in the server's response.


* Error Handling: Provides basic 404 Not Found and 501 Not Implemented responses for unsupported requests.

<h2> Usage </h2>


* Compile the project using a C compiler that supports POSIX socket APIs (e.g., GCC on Linux or MinGW on Windows).

* After compilation, execute the generated executable.
By default, the server listens on port 8080. You can change this by modifying the PORT constant in main.c.

*Use a web browser or HTTP client tool (e.g., curl or Postman) to send GET and POST requests to http://localhost:8080.

## Contributing
If you are interested in contributing to the Photo Stream, please feel free to submit a pull request. We welcome all contributions!


