#include <iostream>
#include <vector>
#include <string>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = 0;
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] += val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid)
                update(2 * node, start, mid, idx, val);
            else
                update(2 * node + 1, mid + 1, end, idx, val);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) +
               query(2 * node + 1, mid + 1, end, l, r);
    }

public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * size);
        build(1, 1, n);
    }

    void addEvent(int day) {
        update(1, 1, n, day, 1);
    }

    int countEvents(int left, int right) {
        return query(1, 1, n, left, right);
    }
};

int main() {
    const int MONTHS = 12;
    SegmentTree calendar(MONTHS);
    vector<vector<string>> eventDetails(MONTHS + 1); // 1-based index for months

    int choice;
    do {
        cout << "\nSchool Event Calendar Menu:\n";
        cout << "1. Add Event\n";
        cout << "2. Show Total Events in the Year\n";
        cout << "3. View Events in a Month\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int month;
            string title;
            cout << "Enter month (1-12): ";
            cin >> month;
            cin.ignore(); // flush newline
            cout << "Enter event title: ";
            getline(cin, title);

            calendar.addEvent(month);
            eventDetails[month].push_back(title);
            cout << "Event added in month " << month << ".\n";

        } else if (choice == 2) {
            int total = calendar.countEvents(1, MONTHS);
            cout << "Total events in the year: " << total << "\n";

        } else if (choice == 3) {
            int month;
            cout << "Enter month to view events (1-12): ";
            cin >> month;

            if (eventDetails[month].empty()) {
                cout << "No events in month " << month << ".\n";
            } else {
                cout << "Events in month " << month << ":\n";
                for (const string& event : eventDetails[month]) {
                    cout << "- " << event << "\n";
                }
            }
        }

    } while (choice != 4);

    cout << "Goodbye!\n";
    return 0;
}