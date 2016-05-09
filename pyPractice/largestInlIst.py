class Solution(object):
    def topKFrequent(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        freq = {}
        for n in nums:
            if n in freq:
                freq[n]+=1
            else:
                freq[n]=1
        
        largest = []
        print(freq)
        for key, value in freq.iteritems():
            if not largest:
                largest.append(value)
            elif key > freq[largest[0]]:
                largest.insert(0,value)
            else:
                largest.append(value)

        return largest[:2]