open Jest;
open ExpectJs;
open JsonWebToken;

type testPayload = {
  foo: string
};

type decodedPayload = {
  foo: string,
  iat: float,
};

let encodeTestPayload = (payload: testPayload) => {
  Json_encode.(
    object_([("foo", string(payload.foo))])
  );
};

let decodeTestPayload = (payload: Js.Json.t) => {
  Json_decode.{
    foo: payload |> field("foo", string),
    iat: payload |> field("iat", float),
  };
};

describe("JsonWebToken", () => {
  let options = Some({ ...emptyOptions, algorithm: HS256 });
  let secret = `string("secret");
  let testPayload = { foo: "bar"};
  let payload = `json(encodeTestPayload(testPayload));
  let result = sign(~secret, ~options, payload);

  describe("sign function", () => {
    test("should produce a string value", () => {
      expect(result)
      |> toBeTruthy
    });

    test("should produce a token that can be verified", () => {
      expect(JsonWebToken.verify(result, secret))
      |> toBeTruthy
    });
  })
  
  describe("decode function", () => {
    test("should return a Js.Json.t with property foo on it", () => {
        JsonWebToken.decode(result)
        |> decodeTestPayload
        |> (x) => x.foo
        |> expect
        |> toEqual("bar")
    });
  });
});