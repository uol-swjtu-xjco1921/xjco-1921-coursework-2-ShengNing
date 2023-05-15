# XJCO 1921 Coursework 2
# Arthur: Sheng Ning

**Run the program with:**

make all
./routeDealing "filepath"
make clean

**The verification of read file.**
1. The id should be identical for each type of data.
2. The node in each data should be existed in the file.
3. Only the link with existed way id could get through.


**The messages and return codes in this coursework:**

| Value | String                                        | Condition                          |
|-------|-----------------------------------------------|------------------------------------|
| 1     | ERROR: Bad Argument Count                     | Program given wrong # of arguments |
| 2     | ERROR: Bad Input File                         | Program fails to open file         |
| 3     | ERROR: Bad Data                               | File has illegal datas             |
| 4     | ERROR: Bad POI                                | POI too long                       |
| 5     | ERROR: Bad Attribute Name                     | Attribute Name too long            |
| 6     | ERROR: Repeat Id                              | Exist repeat id                    |
| 8     | ERROR: Repeated attribute name                | Exist repeat attribute name        |
| 8     | ERROR: Unknown Node                           | Discover node which unexist        |
| 9     | ERROR: Unknown Link                           | Discover link which unexist        |
| 10    | ERROR: Unknown Attribute                      | Discover attribute which unexist   |
| 11    | ERROR: Unapproachable nodes pair              | Nodes pair is unapproachable       |
| 12    | ERROR: The attribute numbers reach the limit. | The attribute numbers reach limit  |
| 100   | ERROR: Miscellaneous (text description)       | Any other error which is detected  |