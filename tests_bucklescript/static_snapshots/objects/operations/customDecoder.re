[@ocaml.ppx.context
  {
    tool_name: "migrate_driver",
    include_dirs: [],
    load_path: [],
    open_modules: [],
    for_package: None,
    debug: false,
    use_threads: false,
    use_vmthreads: false,
    recursive_types: false,
    principal: false,
    transparent_modules: false,
    unboxed_types: false,
    unsafe_string: false,
    cookies: [],
  }
];
module StringOfInt = {
  let parse = string_of_int;
  let serialize = int_of_string;
  type t = string;
};
module IntOfString = {
  let parse = int_of_string;
  let serialize = string_of_int;
  type t = int;
};
module MyQuery = {
  module Raw = {
    type t_variousScalars = {
      .
      "string": string,
      "int": int,
    };
    type t = {. "variousScalars": t_variousScalars};
  };
  let query = "query   {\nvariousScalars  {\nstring  \nint  \n}\n\n}\n";
  type t_variousScalars = {
    .
    "string": IntOfString.t,
    "int": StringOfInt.t,
  };
  type t = {. "variousScalars": t_variousScalars};
  let parse: Raw.t => t =
    value => {
      let variousScalars = {
        let value = value##variousScalars;
        let int = {
          let value = value##int;
          StringOfInt.parse(value);
        }
        and string = {
          let value = value##string;
          IntOfString.parse(value);
        };
        {"string": string, "int": int};
      };
      {"variousScalars": variousScalars};
    };
  let serialize: t => Raw.t =
    value => {
      let variousScalars = {
        let value = value##variousScalars;
        let int = {
          let value = value##int;
          StringOfInt.serialize(value);
        }
        and string = {
          let value = value##string;
          IntOfString.serialize(value);
        };
        {"string": string, "int": int};
      };
      {"variousScalars": variousScalars};
    };
  let definition = (parse, query, serialize);
  module Z__INTERNAL = {
    type root = t;
    type nonrec graphql_module;
    /****--- GraphQL PPX Module ---**

The contents of this module are automatically generated by `graphql-ppx`.
The following is simply an overview of the most important variables and types that you can access from this module.

```
module MyQuery {
  // This is the stringified representation of your query, which gets sent to the server.
  let query: string;

  // This is the main type of the result you will get back.
  // You can hover above the identifier key (e.g. query or mutation) to see the fully generated type for your module.
  type t;

  // This function turns your raw result from the server into the reason/ocaml representation of that result.
  // Depending on your graphql client library, this process should happen automatically for you.
  let parse: Raw.t => t;

  // This function will prepare your data for sending it back to the server.
  // Depending on your graphql client library, this process should happen automatically for you.
  let serialize: t => Raw.t;

  // The definition tuple is primarily used to interact with client libraries.
  // The types are equivalent to: (parse, query, serialize).
  // Your client library will use these values to provide the properly parsed / serialized data for you.
  let definition: (
    Raw.t => t,
    string,
    t => Raw.t
  );

  // This is the representation of your raw result coming from the server.
  // It should not be necessary to access the types inside for normal use cases.
  module Raw: { type t; };
}
```*/
    let graphql_module: graphql_module = Obj.magic(0);
  };
};
