//Kevin Grajeda
//rec14
//Recursion

#include <iostream>
using namespace std;

//Task 1
bool hasEvenOnes(int binary) {
    if (binary == 0) {
        return true;
    }
    if (binary == 1) {
        return false;
    }

    return hasEvenOnes(binary/10) * binary%10;
}
//Task 2
struct Node {
    Node(int data = 0, Node* next = nullptr)
        : data(data), next(next){}
    int data;
    Node* next;
};
Node* listSum(Node* list1, Node* list2) {
    if (list1 == nullptr && list2 == nullptr) {
        return nullptr;
    }
    if (list1 == nullptr) {
        return list2;
    }
    if (list2 == nullptr) {
        return list1;
    }
    Node* result = new Node(list1->data+list2->data, nullptr);
    result->next = listSum(list1->next, list2->next);
    return result;
}
//Task 3
struct TNode {
    TNode(int data = 0, TNode* left = nullptr, TNode* right = nullptr)
        : data(data), left(left), right(right) {}
    int data;
    TNode* left, * right;
};
int max(TNode* root) {
    if (root == nullptr) {
        invalid_argument myInvalidArg("Tree is empty");
        throw myInvalidArg;
    }
    int maxNode = root->data;
    if (root->left != nullptr) {
         int lmaxNode =  max(root->left);
         if (lmaxNode > maxNode) {
             maxNode = lmaxNode;
         }
    }
    if (root->right != nullptr) {
        int rmaxNode = max(root->left);
        if (rmaxNode > maxNode) {
            maxNode = rmaxNode;
        }
    }
    return maxNode;
}
//Task 4
bool palindrome(char* s, int len) {
    if (len < 1) {
        return true;
    }
    if (*(s + 0) != *(s + len - 1)) {
        return false;
    }
    return palindrome(s + 1, len - 2);
}
//Task 5
int towers(int n, char start, char target, char spare) {
    int count = 0;
    if (n == 0) {
        return count+=0;
    }
    count++;
    count +=towers(n - 1, start, spare, target);
    count +=towers(n - 1, spare, target, start);
    return count;
}
//Task 6
void mystery(int n) {
    if (n > 1) {
        cout << 'a';
        mystery(n / 2);
        cout << 'b';
        mystery(n / 2);
    }
    cout << 'c';
}
int main() {
   //Task 1
   bool x = hasEvenOnes(0111101100110111);
   cout << x << endl;

   //Task 2
    Node* list1 = new Node(1, nullptr);
    list1->next = new Node(2, nullptr);
    list1->next->next = new Node(3, nullptr);
    list1->next->next->next = new Node(4, nullptr);
    Node* list2 = new Node(7, nullptr);
    list2->next = new Node(6, nullptr);
    list2->next->next = new Node(7, nullptr);
    list2->next->next->next = new Node(8, nullptr);
    list2->next->next->next->next = new Node(9, nullptr);
    Node* list3 = listSum(list1, list2);
    cout << list3->data << " " << list3->next->data << " " << list3->next->next->data << " " << list3->next->next->next->data << " " << list3->next->next->next->next->data;

    //Task 3
    TNode a(1), b(2), c(4), d(8, &a, &b), e(32, &c), f(32, &d, &e);
    cout << endl;
    cout << max(&f) << endl;
    try {
        max(&f);
    }
    catch (const std::invalid_argument & ia) {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
    }

    //Task 4
    char s[] = "dracecard";
    if (palindrome(s, 9)) { cout << "Yes!\n"; }

    //Task 5
    cout << towers(10, 'A', 'C', 'B');

    //Task 6
    mystery(10);
    // 0. c
    // 1. c
    // 2. acbcc
    // 3. acbcc
    // 4. aacbccbacbccc
    // 5. aacbccbacbccc
    // 6. aacbccbacbccc 
    // 7. aacbccbacbccc
    // 8. aaacbccbacbcccbaacbccbacbcccc
    // 9. aaacbccbacbcccbaacbccbacbcccc
    // 10. aaacbccbacbcccbaacbccbacbcccc
}