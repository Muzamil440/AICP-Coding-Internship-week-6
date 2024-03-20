#include <iostream>
#include <string>

using namespace std;

class WildLifePark {
private:
    static int bookingNumber;
    string ticketTypes[5] = {"Adult", "Child", "Senior", "Family", "Group"};
    float dayOnePrices[5] = {20.00, 12.00, 16.00, 60.00, 15.00};
    float dayTwoPrices[5] = {30.00, 18.00, 24.00, 90.00, 22.50};
    float extraAttractionPrices[3] = {2.50, 2.00, 5.00};
    int childLimitPerAdult = 2;
    int groupThreshold = 6;

public:
    WildLifePark() { bookingNumber++; }

    void displayOptions() {
        cout << "One-day ticket options:" << endl;
        displayPrices(dayOnePrices);
        cout << "\nTwo-day ticket options:" << endl;
        displayPrices(dayTwoPrices);
        cout << "\nExtra attractions:" << endl;
        cout << "1. Lion Feeding: $" << extraAttractionPrices[0] << " per person" << endl;
        cout << "2. Penguin Feeding: $" << extraAttractionPrices[1] << " per person" << endl;
        cout << "3. Evening Barbecue (two-day tickets only): $" << extraAttractionPrices[2] << " per person" << endl;
    }

    void displayPrices(float prices[]) {
        for (int i = 0; i < 5; i++) {
            cout << ticketTypes[i] << ": $" << prices[i] << endl;
        }
    }

    bool isValidTicketType(string ticketType) {
        for (int i = 0; i < 5; i++) {
            if (ticketType == ticketTypes[i]) {
                return true;
            }
        }
        return false;
    }

    bool isValidNumberOfDays(int days) {
        return days == 1 || days == 2;
    }

    void processBooking() {
        string ticketType;
        int numTickets, numDays;
        cout << "Enter ticket type (Adult/Child/Senior/Family/Group): ";
        cin >> ticketType;
        if (!isValidTicketType(ticketType)) {
            cout << "Invalid ticket type!" << endl;
            return;
        }
        cout << "Enter number of tickets: ";
        cin >> numTickets;
        if (cin.fail() || numTickets <= 0) {
            cout << "Invalid number of tickets!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
        cout << "Enter number of days (1 for one-day ticket, 2 for two-day ticket): ";
        cin >> numDays;
        if (!isValidNumberOfDays(numDays)) {
            cout << "Invalid number of days!" << endl;
            return;
        }

        float totalPrice = calculateTicketPrice(ticketType, numTickets, numDays);
        totalPrice += calculateExtraAttractionPrice(numTickets, numDays);

        cout << "\nBooking Details:" << endl;
        cout << "Booking Number: " << bookingNumber << endl;
        cout << "Total Price: $" << fixed << totalPrice << endl;
    }

    float calculateTicketPrice(string ticketType, int numTickets, int numDays) {
        float* prices = (numDays == 1) ? dayOnePrices : dayTwoPrices;
        for (int i = 0; i < 5; i++) {
            if (ticketType == ticketTypes[i]) {
                return prices[i] * numTickets;
            }
        }
        return 0.0; // Return 0 if ticket type not found (should not occur)
    }

    float calculateExtraAttractionPrice(int numTickets, int numDays) {
        float totalExtraPrice = 0.0;
        char choice;
        cout << "Do you want to include Lion Feeding? (Y/N): ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            totalExtraPrice += extraAttractionPrices[0] * numTickets;
        }
        cout << "Do you want to include Penguin Feeding? (Y/N): ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            totalExtraPrice += extraAttractionPrices[1] * numTickets;
        }
        if (numDays == 2) {
            cout << "Do you want to include Evening Barbecue? (Y/N): ";
            cin >> choice;
            if (choice == 'Y' || choice == 'y') {
                totalExtraPrice += extraAttractionPrices[2] * numTickets;
            }
        }
        return totalExtraPrice;
    }
};

int WildLifePark::bookingNumber = 0;

int main() {
    WildLifePark park;
    park.displayOptions();
    park.processBooking();

    return 0;
}
