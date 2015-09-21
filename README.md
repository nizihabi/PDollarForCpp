# PDollarForCpp
$P Cloude Gesture Recognizer for cpp

The $P Point-Cloud Recognizer is a 2-D gesture recognizer designed for rapid prototyping of gesture-based user interfaces. In machine learning terms, $P is an instance-based nearest-neighbor classifier with a Euclidean scoring function, i.e., a geometric template matcher. $P is the latest in the dollar family of recognizers that includes $1 for unistrokes and $N for multistrokes. Although about half of $P's code is from $1, unlike both $1 and $N, $P does not represent gestures as ordered series of points (i.e., strokes), but as unordered point-clouds. By representing gestures as point-clouds, $P can handle both unistrokes and multistrokes equivalently and without the combinatoric overhead of $N. When comparing two point-clouds, $P solves the classic assignment problem between two bipartite graphs using an approximation of the Hungarian algorithm. 

This Dll is builded for cpp baseed on the CSharp version.

More details please view on <a>http://depts.washington.edu/aimgroup/proj/dollar/pdollar.html</a>
