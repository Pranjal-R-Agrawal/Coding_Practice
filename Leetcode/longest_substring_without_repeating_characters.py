class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        longest_length, start = 0, 0
        index = dict()

        for i, c in enumerate(s):
            if c in index:
                start = max(start, index[c] + 1)

            longest_length = max(longest_length, i - start + 1)
            index[c] = i

        return longest_length
