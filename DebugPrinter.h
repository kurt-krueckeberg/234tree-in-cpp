/* 
 * File:   DebugPrinter.h
 * Author: kurt
 *
 * Created on May 11, 2013, 8:21 PM
 */

#ifndef DEBUGPRINTER_H
#define	DEBUGPRINTER_H
#include <iosfwd>
#include <string>
#include <sstream>

template<typename K> class Tree234;// fwd reference

class DebugPrinter {
    
    std::ostream& ostr_;
    
public:
    DebugPrinter(std::ostream& ostr) : ostr_(ostr) {}
    DebugPrinter(const DebugPrinter& tp) : ostr_(tp.ostr_) {}
    template<class K> std::ostream& operator()(K k, int index, const typename Tree234<K>::Node234 *current, bool isRoot);
};

template<class K> inline std::ostream& DebugPrinter::operator()(K key, int index, const typename Tree234<K>::Node234 *current, bool isRoot)
{

    const typename Tree234<K>::Node234 *parent = current->getParent();

    int child_index; // This means the parent is nullptr and current is therefore the root.
    
    if (parent != nullptr) {
    
        for (child_index = 0; child_index <= parent->getTotalItems(); ++child_index) {
       
             if (current == parent->children[child_index]) { 
                 break;
            }  
        }
    } 
    
    std::ostringstream oss;
    
    if (parent != nullptr) {
        
        oss << " address(" << current << "): key[" << index << "] = " << key <<  ": parent[" << parent << "]->children[" << child_index << "]->keys[" << index << "] = " << key << "\n";
        
    } else {
        
        oss << " address(" << current << "): key[" << index << "] = " << key <<  ": root\n";
    }

    std::string suffix = oss.str();
  //--std::string suffix("some junk");

    switch (current->getTotalItems()) {
    
      case 1: // 2-node
              ostr_ << "\nTwo node:  " << suffix;
              break;
    
      case 2: // 3-node

              ostr_ << "\nThree node:" << suffix; 
              break;
    
      case 3: // 4-node
              ostr_ << "\nFour node: " << suffix; 
              break;
    }

    return ostr_;
}

#endif	/* DEBUGRINTER_H */