/**
 * This is a utility module
 */
// This file is auto-generated, don't edit it. Thanks.

using System;
using System.Collections.Generic;
using System.IO;

using Tea;

namespace AlibabaCloud.TeaUtil.Models
{
    public class ExtendsParameters : TeaModel {
        [NameInMap("headers")]
        [Validation(Required=false)]
        public Dictionary<string, string> Headers { get; set; }

        [NameInMap("queries")]
        [Validation(Required=false)]
        public Dictionary<string, string> Queries { get; set; }

    }

}
