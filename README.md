# XJCO 1921 Coursework 2
# Arthur: Sheng Ning

## Table of Content
- [Background](#Background)
- [Install](#Install)
- [Usage](#Usage)
- [Data Intro](#Data-Intro)
- [Functions](#Functions)
- [Errors List](#Errors-List)
  - [Data verification](#Data-verification)
  - [File format](#File-format)

# Background

This repository is code for XJCO 1921 Assignment 2.

# Install

This project use SDL to implement the graphic shown. Go check them out if you don't have them locally installed.

```
yay -S SDL2
```

# Usage

```
make all

./routeDealing "filepath"

make clean
```

If the file was read successfully, a terminal will be appeared.

User could type number to choose the option.

# Data-Intro

This project read a map, which contains 5 main attributes: bounding, link, node, way, geom.

Each attribute have an unique id.

<p></p>
<p></p>

**For bounding:**

bounding has 4 basic attributes: maxLon, minLon, maxLat, minLat

which means the shown map's range.

<p></p>
<p></p>

**For link:**

link has 4 basic attributes: id, node1, node2, length.

node1 and node2 is id of node, means the point of link.

length is the length of link.

<p></p>
<p></p>

*These attribute should be in read file.*

link could be added attributes: speedLimit, POI, ......

speedLimit is an attribute which will be initialized as 60KM/H if it doesn't be read in file.

POI and other attributes could be added customized, but no more than 15.

Meanwhile, length of POI and added attributes name should under 15 char.

<p></p>
<p></p>


**For node:**

node has 3 basic attributes: id, lat, lon.

lat means the latitude.

lon means the longitude.

<p></p>
<p></p>

**For way and geom:**

way and geom has these basic attributes: id, size, nodelist[]

size means the number of nodes the way/geom contained, which only store in struct but not in file.

the nodelist store the nodes in the way/geom.


# Functions

This project allow to find:

1. *Shortest path* between two nodes with assign POI that need to pass.

2. *Fastest path* between two nodes with assign POI that need to pass.

And shows the path in the map with SDL.

<p></p>
<p></p>

Meanwhile, this project allow to edit the map:

1. Edit the link attribute except basic attribute.
  - Add new attributes.
  - Change the value of old attributes.

2. Add a new link which obey the data specification.

After edition, an edited map could be writen in file, and read to reload the edited data.

# Errors-List

**The messages and return codes in this coursework:**

| Value | String                                        | Condition                          |
|-------|-----------------------------------------------|------------------------------------|
| 1     | ERROR: Bad Argument Count                     | Program given wrong # of arguments |
| 2     | ERROR: Bad Input File                         | Program fails to open file         |
| 3     | ERROR: Bad Data                               | File has illegal data              |
| 4     | ERROR: Bad POI                                | POI too long                       |
| 5     | ERROR: Bad Attribute Name                     | Attribute Name too long            |
| 6     | ERROR: Repeat Id                              | Exist repeat id                    |
| 8     | ERROR: Repeated attribute name                | Exist repeat attribute name        |
| 8     | ERROR: Unknown Node                           | Discover node which not exist      |
| 9     | ERROR: Unknown Link                           | Discover link which not exist      |
| 10    | ERROR: Unknown Attribute                      | Discover attribute which not exist |
| 11    | ERROR: Unapproachable nodes pair              | Nodes pair is unapproachable       |
| 12    | ERROR: The attribute numbers reach the limit. | The attribute numbers reach limit  |
| 100   | ERROR: Miscellaneous (text description)       | Any other error which is detected  |

# Data-verification

1. The id should be identical for each type of data.
2. The node in each data should be existed in the file.
3. The data should be in range: longitude and latitude should be in [-90, 90].
4. The data should be in range: length and speedLimit should be a positive value.
5. Only the link with existed way id could get through.

# File-format

Each line should begin with "<" and end with">"

The first String should be "link", "node", "way", or "geom".

Then follow with "'attribute name'='attribute value'", separate by a space.

<p></p>
<p></p>

For example:
```text
<bounding minLat=53.801600 minLon=-1.564000 maxLat=53.811000 maxLon=-1.543100 /bounding>

<link id=-2143392632 node=-2554 node=-2552 way=-7720 length=0.948234 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>

<node id=921345544 lat=53.806376 lon=-1.563695 /node>

<way id=16171809 node=52635273 node=163639535 /way>

<geom id=84749914 node=984246772 node=984246773 node=984246775 node=984246776 node=984246772 /geom>
```
