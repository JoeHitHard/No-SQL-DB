# No-SQL Database Engine 🔥

A lightweight, file-based No-SQL database engine built from scratch in **C**, designed to handle key-value data with versioning support. Perfect for learning database internals or embedding into resource-constrained environments. 

![C Language](https://img.shields.io/badge/C-Expert-blue?logo=c)
![Versioning](https://img.shields.io/badge/Data%20Versioning-Supported-green)
![License](https://img.shields.io/badge/License-MIT-red)

---

## 🛠 Technologies Used
- **Core Language**: C (with `stdio.h`, `stdlib.h`, `string.h`)
- **Data Structures**: Custom implementations of hash tables, linked lists, and dynamic arrays.
- **Version Control**: Column-level versioning for audit trails.
- **Persistence**: Logging operations to `log.txt` for durability.
- **Memory Management**: Manual memory allocation/reallocation with optimizations for scalability.

---

## 🚀 Features
- **CRUD Operations**: `create`, `put`, `get`, `delete` tables and records.
- **Schema-less Design**: Flexible key-value pairs with dynamic column support.
- **Data Versioning**: Track historical changes at the column level (e.g., see previous values of a field).
- **Atomic Transactions**: Commit updates safely with version consistency checks.
- **Query Logging**: All operations are logged to `log.txt` with timestamps.
- **Lightweight**: No external dependencies—just compile and run!

---

## 🛠 Getting Started

### Prerequisites
- GCC compiler
- Basic terminal familiarity

### Installation
1. Clone the repo:
   ```bash
   git clone https://github.com/JoeHitHard/No-SQL-DB.git
   cd No-SQL-DB/DB\ Engine
   
2. Compile the code:
   ```bash
   gcc main.c -o nosql_db
   ```
3. Run the executable:
   ```bash
   ./nosql_db
   ```

---

## 💻 Usage Examples

### Create a Table
```sql
create users;
```
*Output*: `Table "users" has been created.`

### Insert Data
```sql
put users key=joe id=joe1 age=28 email=joe@dev.com;
```
*Output*: `Row Inserted.`

### Retrieve Data
```sql
get users joe;
```
*Output*:
```
          joe:           id:           joe1 Version: 1
                       age:             28 Version: 1
                     email:   joe@dev.com Version: 1
```

### Delete Data
```sql
delete users joe;
```
*Output*: `Row Deleted.`

### Advanced Query (Get All Rows)
```sql
get users all;
```
*Output*: Displays all rows in the `users` table.

---

## 🎯 Use Cases
1. **Configuration Storage**: Store app settings with version history.
2. **User Profiles**: Manage flexible user attributes without rigid schemas.
3. **IoT Data Logging**: Capture sensor readings with timestamps and versions.
4. **Educational Tool**: Learn how databases handle CRUD and memory management.

---

## 🔮 Future Enhancements
- [ ] Add support for **indexes** to speed up queries.
- [ ] Implement a `rollback` command to revert to previous versions.
- [ ] Add network support for remote connections.
- [ ] Support JSON export/import for interoperability.

---

⭐ **Star this repo if you love minimalist, performant systems!** ⭐
