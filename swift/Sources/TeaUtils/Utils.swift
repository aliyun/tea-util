//
// Created by Axios on 2020/2/17.
//

import Foundation

func isBool(_ val: Any?) -> Bool {
    if val == nil {
        return false
    }
    if val is Bool {
        return true
    }
    return false
}
