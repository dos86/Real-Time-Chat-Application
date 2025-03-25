# Real-Time-Chat-Application

#### Overview:
This project is a real-time chat application where users can send and receive messages over a network. It demonstrates key C++ features such as **networking (TCP/IP)**, **multithreading**, and **STL**. Optionally, it can include **SQL integration** for storing chat history in a Microsoft SQL Server database.

---

### Key Features:
1. **Client-Server Architecture**:
   - The server handles multiple clients concurrently using multithreading.
   - Clients connect to the server via TCP/IP sockets.

2. **Message Broadcasting**:
   - Messages sent by one client are broadcast to all connected clients in real time.

3. **STL Usage**:
   - Use `std::vector` or `std::unordered_map` to manage connected clients.
   - Use `std::thread` and `std::mutex` for thread-safe operations.

4. **Optional SQL Integration**:
   - Store chat messages in a Microsoft SQL Server database for persistence.
   - Allow users to retrieve past messages from the database.

5. **Error Handling**:
   - Handle disconnections gracefully.
   - Ensure thread safety when accessing shared resources.

---

### Folder Structure:
```
RealTimeChat/
├── include/
│   ├── Client.hpp          // Client class definition
│   ├── Server.hpp          // Server class definition
│   ├── Message.hpp         // Message struct definition
│   └── Database.hpp        // Optional: SQL database wrapper
├── src/
│   ├── Client.cpp
│   ├── Server.cpp
│   ├── Message.cpp
│   └── Database.cpp        // Optional: SQL implementation
├── main.cpp                // Main entry point
├── CMakeLists.txt          // Build configuration
└── README.md               // Project documentation
```

---

### Workflow:
1. **Server**:
   - Listens for incoming client connections.
   - Maintains a list of connected clients.
   - Broadcasts messages received from one client to all other clients.

2. **Client**:
   - Connects to the server via TCP/IP.
   - Sends messages to the server and displays messages received from other clients.

3. **Database (Optional)**:
   - Stores chat messages in a table (`Messages`) with columns: `Timestamp`, `Sender`, `Message`.
   - Allows users to query past messages.

---

### Technologies Used:
1. **STL**: `std::vector`, `std::unordered_map`, `std::thread`, `std::mutex`.
2. **OOP**: Encapsulation and modularity in designing `Client`, `Server`, and `Database` classes.
3. **Multithreading**: Concurrent handling of multiple clients using threads.
4. **Networking**: TCP/IP sockets for client-server communication.
5. **SQL**: Interaction with Microsoft SQL Server using ODBC (optional).

---

### Example Use Case:
- A user starts the server application.
- Multiple clients connect to the server and join the chat room.
- When a client sends a message, the server broadcasts it to all connected clients.
- Optionally, the server stores the message in a database for later retrieval.
