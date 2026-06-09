#ifndef TRANSACTIONLOG_H
#define TRANSACTIONLOG_H

#include <iostream>
#include <cstring>

#define MAX_LOG_ENTRIES 100

// Simple fixed-size string for log messages (avoids std::string)
struct LogEntry {
    char message[256];
    LogEntry() { message[0] = '\0'; }
    LogEntry(const char* msg) {
        strncpy(message, msg, 255);
        message[255] = '\0';
    }
};

// Template class: works with Product, Supplier, or any type
template <typename T>
class TransactionLog {
private:
    LogEntry logHistory[MAX_LOG_ENTRIES];
    int      entryCount;

    // Helper: convert number to string manually
    void appendInt(char* buf, int bufSize, int val) const {
        char tmp[30];
        int  i = 0, neg = 0;
        if (val < 0) { neg = 1; val = -val; }
        if (val == 0) { tmp[i++] = '0'; }
        while (val > 0) { tmp[i++] = '0' + (val % 10); val /= 10; }
        if (neg) tmp[i++] = '-';
        // reverse
        int len = (int)strlen(buf);
        for (int j = i - 1; j >= 0 && len < bufSize - 1; j--)
            buf[len++] = tmp[j];
        buf[len] = '\0';
    }

public:
    TransactionLog() : entryCount(0) {}

    // Record a plain-text action
    void recordAction(const char* action, const T& entity) {
        if (entryCount >= MAX_LOG_ENTRIES) {
            std::cout << "TransactionLog full. Cannot record more entries.\n";
            return;
        }
        char buf[256];
        strncpy(buf, action, 100);
        buf[100] = '\0';
        strncat(buf, " -> ", 5);

        // Use operator<< to get a string representation via a temporary stream
        // We do this through a simple char buffer trick using snprintf
        // Since we avoid complex libraries, we just print the entity inline
        logHistory[entryCount++] = LogEntry(buf);

        // Print immediately as well (audit trail in real-time)
        std::cout << "[LOG #" << entryCount << "] " << buf << entity << "\n";
    }

    // Record with a custom message only
    void recordAction(const char* message) {
        if (entryCount >= MAX_LOG_ENTRIES) {
            std::cout << "TransactionLog full.\n";
            return;
        }
        logHistory[entryCount++] = LogEntry(message);
        std::cout << "[LOG #" << entryCount << "] " << message << "\n";
    }

    void printAuditTrail() const {
        std::cout << "====== AUDIT TRAIL (" << entryCount << " entries) ======\n";
        for (int i = 0; i < entryCount; i++) {
            std::cout << "  [" << (i + 1) << "] " << logHistory[i].message << "\n";
        }
        std::cout << "==========================================\n";
    }

    int getEntryCount() const { return entryCount; }
};

#endif // TRANSACTIONLOG_H
