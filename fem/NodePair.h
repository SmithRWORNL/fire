/**----------------------------------------------------------------------------
 Copyright (c) 2015-, UT-Battelle, LLC
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 * Neither the name of fern nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 Author(s): Jay Jay Billings (jayjaybillings <at> gmail <dot> com)
 -----------------------------------------------------------------------------*/
#ifndef FEM_NODEPAIR_H_
#define FEM_NODEPAIR_H_

#include <FEMTypes.h>

namespace fire {

/**
 * This class provides a basic pair of nodes. It is templated so that the
 * exact type of node is configurable, which is useful for changing the
 * dimensionality of a problem without rewriting downstream code. It serves as
 * the base class for 2D boundary conditions as well, such as the 2D Dirichlet
 * and Robin conditions.
 *
 * It requires for simplicity's sake that the two nodes be the same type.
 *
 * NodePairs must be created from existing nodes. They do not take ownership
 * of the nodes or make copies. They only work with references.
 */
template<typename T> // FIX ME! Needs to be restricted to node types.
struct NodePair {
public:

	/**
	 * The first node where the edge starts
	 */
	T firstNode;

	/**
	 * The second node where the edge terminates
	 */
	T secondNode;

	/**
	 * Constructor
	 */
	NodePair(const T & first, const T & second) : firstNode(first),
			secondNode(second) {};

	/**
	 * Destructor
	 */
	virtual ~NodePair() {};

	/**
	 * This operator override makes it possible to easily check if two pairs
	 * are equal.
	 */
	bool operator == (const NodePair & otherPair) const {
		return firstNode == otherPair.firstNode
				&& secondNode == otherPair.secondNode;
	};

	/**
	 * This operator override makes it possible to easily check if two pairs
	 * are not equal.
	 * @param otherPair the node to compare against
	 * @return true if the node pairs are equal, false if not
	 */
	bool operator != (const NodePair & otherPair) const {
		return !operator==(otherPair);
	};

	/**
	 * This operation returns true if the nodes in this pair are equal such
	 * that a line "drawn between them" would in fact form a loop.
	 * @return true if the nodes form a (self-)loop, false if not.
	 */
	bool isLoop() {
		return firstNode == secondNode;
	}

};

} /* namespace fire */

#endif /* FEM_NODEPAIR_H_ */
