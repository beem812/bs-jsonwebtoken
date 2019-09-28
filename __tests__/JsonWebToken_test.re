open Jest;
open ExpectJs;
open JsonWebToken;
open Json_encode;

type testPayload = {
  foo: string
};

let encodeTestPayload = (payload: testPayload) => {
  object_([("foo", string(payload.foo))]);
};

describe("sign function", () => {
  let options = Some({ ...emptyOptions, algorithm: HS256, notBefore: "2 days"});
  let secret = `string("secret");
  let testPayload = { foo: "bar"};
  let payload = `json(encodeTestPayload(testPayload));
  let result = sign(~secret, ~options, payload);

  test("should produce a string value", () => {
    expect(result)
    |> toBeTruthy
  });

  test("should produce a token that can be verified", () => {
    Js.log(JsonWebToken.verify(result, secret));
    expect(JsonWebToken.verify(result, secret))
    |> toBeTruthy
  });

  test("should decode a js object with foo, nbf, and iat properties", () => {
    expect(JsonWebToken.decode(result))
    |> toContainProperties([|"foo", "nbf", "iat"|])
  })
})