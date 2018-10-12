# using dfs solution


def is_legal(l, c):
    '''
    result : list of queen that already exists
    c : int that means where we want to put now queen. c means the c+1th column
    '''
    for i in range(l):
        if abs(c-result[i]) in (0, l-i):
            return False
    return True


def dfs(n=0):
    # start dfs using recursion
    if n == 7:
        for i in range(8):
            if is_legal(n, i):
                global count
                count += 1
                result[n] = i
                _print(result, count)
    for c in range(8):
        if is_legal(n, c):
            result[n] = c
            if n == 8:
                print result
            else:
                dfs(n+1)


def _print(re, c):
    print ('#%d result\n' % c)
    for i in re:
        line = 'o  '*(i-0)+'x  '+'o  '*(7-i)
        print line
    print ('='*15)


if __name__ == '__main__':
    result = [-1]*8
    count = 0
    dfs()
