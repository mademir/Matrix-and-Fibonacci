#include <iostream>
#include <ctime>
using namespace std;

///Declarations:
int fibonacci_recursive(int limit, int ct = 3, int n1 = 1, int n2 = 1); ///Default values are set for the counter to start at 3, n1 and n2 to be equal to 1 as thats the value for the first two term.
int fibonacci_iterative(int limit);

/** Fibonacci sequence is the sequence where the first two terms are 1
 * and each term after that is the sum of the previous two terms (e.g. third term is 1 + 1 = 2).
 * 
 * To implement the function recursively, the function should have a function call for itself, inside the function.
 * Starting values for the first two term shoul be present, and the next term should be set as the sum of the previous two,
 * and should be passed as the parameters for this call so that the new call can calculate the sum of the previous two terms
 * and call the next one until the term wanted is reached, which should be checked by a conditional statement before the call.
 * 
 * To implement the function iteratively, the function should have a loop where it calculates the
 * new value from the previous two on each iteration. And when the desired term is reached, which is
 * checked by the conditional statement of the loop, iteration stops.
*/

/** Calculates the n'th term of the Fibonacci sequence.
 * Uses recursive method to calculate the next term.
 * 'limit' is the n'th term the function will finish at.
 * 'ct' is the counter, starts at 3 as the terms before them are already in place.
 * 'n1' is the the second last value where n1 + n2 equals to new value.
 * 'n2' is the the last value where n1 + n2 equals to new value.
 * Returns the n'th term as an integer.
 */
int fibonacci_recursive(int limit, int ct, int n1, int n2){
    if (limit <= 0) return 0;       ///If the term wanted is 0th term or below that, return 0. (0th term of the Fibonacci sequence is 0.)
    else if (limit <= 2) return 1;  ///Otherwise, if the term wanted is the 1st or the 2nd term, return 1, as it is their value.
    if (ct++ <= limit) return fibonacci_recursive(limit, ct, n2, n1 + n2);      ///If the counter is below or equals to the term wanted, recursively call and return the returned value of this function by passing the limit value, the increased counter, n2 value for the new n1 value and sum of n1 and n2 as the new n2 value (shifting the values and making the next value the sum of the last two, as in Fibonacci series).
    else return n2;     ///If the counter is above the the term wanted, return the last calculated value, which is stored in n2.
}

/** Calculates the n'th term of the Fibonacci sequence.
 * Uses iterative method to calculate the next term.
 * 'limit' is the n'th term the function will finish at.
 * 'ct' is the counter, starts at 3 as the terms before them are already in place.
 * Returns the n'th term as an integer.
 */
int fibonacci_iterative(int limit){
    if (limit <= 0) return 0;       ///If the term wanted is 0th term or below that, return 0. (0th term of the Fibonacci sequence is 0.)
    else if (limit <= 2) return 1;  ///Otherwise, if the term wanted is the 1st or the 2nd term, return 1, as it is their value.
    int n1 = 1, n2 = 1, ct = 3, temp;   ///'n1' is the the second last value and 'n2' is the the last value where n1 + n2 equals to new value. 'ct' is the counter, starts at 3 as the terms before them are already in place. 'temp' is the temporary value to store the sum of the previous two values before shifting.
    while (ct++ <= limit){  ///While the counter is below or equals to the term wanted.. (The counter is increased)
        temp = n1 + n2;     ///The sum of the last two values are stored in temp.
        n1 = n2;            ///The value of n2 is shifted to n1.
        n2 = temp;          ///The sum value stored in temp is set as the new value of n2.
    }
    return n2;              ///Returns the last calculated value, which is stored in n2.
}

///Main function that calculates the sum the first 30 terms in the series and reports how long it takes, for each version.
int main(){
    int sum = 0; ///Values for the sum and to calculate the time are set/declared.

    clock_t t1 = clock();    // return time now

    for(int i = 0; i < 30; i++) sum += fibonacci_recursive(i);      ///The actual loop to calculate the sum of the first 30 terms in the fibonacci series by recursive method. Only one parameter is needed to specify the wanted term as the other parameters have default values.

    clock_t t2 = clock();

    cout << "Sum: " << sum << "\nThe time it took for the recursive method (in milliseconds): " << (((float)(t2-t1))/CLOCKS_PER_SEC) * 1000 << "\n\n"; ///Reporst the sum and the time it took.
//cout << "Sum: " << sum << "\nThe time it took for the recursive method: " << (((float)(t2-t1))/CLOCKS_PER_SEC)*1000 << "\n"; ///Reporst the sum and the time it took.
//cout <<"CLOCKS_PER_SEC: "<< CLOCKS_PER_SEC;
    sum = 0; //Resetting the sum.
    ///The next is for the iterative method.

    t1 = clock();    // return time now

    for(int i = 0; i < 30; i++) sum += fibonacci_iterative(i);      ///The actual loop to calculate the sum of the first 30 terms in the fibonacci series by iterative method.

    t2 = clock();

    cout << "Sum: " << sum << "\nThe time it took for the iterative method (in milliseconds): " << (((float)(t2-t1))/CLOCKS_PER_SEC) * 1000 << "\n"; ///Reporst the sum and the time it took.

    ///The results show that it takes less time to execute the iterative method than it takes the recursive method.

    return 0;
}
