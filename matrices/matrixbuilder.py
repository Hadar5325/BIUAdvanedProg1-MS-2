from random import randint
for n in xrange(10, 51):
    number_list = []
    with open("Matrix" + str(n) + "x" + str(n) + ".txt", 'w', 1024) as matrix:
        for i in range(0, n):
            row_list = []
            for j in range(0, n):
                value = randint(-1, 9)
                row_list.append(value)
            number_list.append(row_list)

        for i in number_list:
            strNums = ""
            for j in i:
                strNums += str(j)
                strNums += ","
            strNums = strNums[:-1]
            matrix.write(strNums)
            matrix.write('\n')
        matrix.write("0,0\n")
        matrix.write(str(n-1) + "," + str(n-1) + "\n")
        matrix.write("end")
        matrix.close()