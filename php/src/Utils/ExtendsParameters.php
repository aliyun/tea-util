<?php

// This file is auto-generated, don't edit it. Thanks.
namespace AlibabaCloud\Tea\Utils\Utils;

use AlibabaCloud\Tea\Model;

class ExtendsParameters extends Model {
    public function validate() {}
    public function toMap() {
        $res = [];
        if (null !== $this->headers) {
            $res['headers'] = $this->headers;
        }
        return $res;
    }
    /**
     * @param array $map
     * @return ExtendsParameters
     */
    public static function fromMap($map = []) {
        $model = new self();
        if(isset($map['headers'])){
            $model->headers = $map['headers'];
        }
        return $model;
    }
    public $headers;

}
