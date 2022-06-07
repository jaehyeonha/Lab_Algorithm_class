#include <iostream>
using namespace std;

int main() {
	int n;
    cin >> n;

    int count = 0;

	for (int i = 0; i < n; i++) {
        int temp;
		cin >> temp;
        int div;

		for (div = 2; div <= temp; div++) {
			if (temp % div == 0){
                break;
            }
		}
        if(temp == div){
            count++;
        }

	}
	cout << count << endl;
}