#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
using namespace std;

/*
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:
Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:
Input: nums = [3,3], target = 6
Output: [0,1] 

Constraints:
2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.

Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
*/

/**
 * Brute-force solution: O(n^2)
 * Checks every pair of elements to find the target sum.
 */
vector<int> twoSumBruteForce(const vector<int>& nums, int target) {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {}; // Should not reach here if one solution exists
}

/**
 * Optimal solution: O(n)
 * Uses a hash map to store complements and find the pair in one pass.
 */
vector<int> twoSumOptimal(const vector<int>& nums, int target) {
    unordered_map<int, int> seen; // value -> index
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (seen.count(complement)) { // if(seen.find(complement) != seen.cend()){
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {}; // Should not reach here if one solution exists
}

/**
 * Helper to validate unordered index pairs
 */
bool isValidPair(const vector<int>& result, const vector<int>& expected) {
    return result.size() == 2 &&
           ((result[0] == expected[0] && result[1] == expected[1]) ||
            (result[0] == expected[1] && result[1] == expected[0]));
}

/**
 * Runs test cases for both implementations
 */
void runTests() {
    // Test 1
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> expected1 = {0, 1};
    assert(isValidPair(twoSumBruteForce(nums1, target1), expected1));
    assert(isValidPair(twoSumOptimal(nums1, target1), expected1));

    // Test 2
    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    vector<int> expected2 = {1, 2};
    assert(isValidPair(twoSumBruteForce(nums2, target2), expected2));
    assert(isValidPair(twoSumOptimal(nums2, target2), expected2));

    // Test 3
    vector<int> nums3 = {3, 3};
    int target3 = 6;
    vector<int> expected3 = {0, 1};
    assert(isValidPair(twoSumBruteForce(nums3, target3), expected3));
    assert(isValidPair(twoSumOptimal(nums3, target3), expected3));

    // Test 4
    vector<int> nums4 = {1, 2, 3, 4, 5, 6};
    int target4 = 11;
    vector<int> expected4 = {4, 5}; // 5 + 6
    assert(isValidPair(twoSumBruteForce(nums4, target4), expected4));
    assert(isValidPair(twoSumOptimal(nums4, target4), expected4));

    cout << "✅ All tests passed successfully!\n";
}

int main() {
    runTests();
    return 0;
}
