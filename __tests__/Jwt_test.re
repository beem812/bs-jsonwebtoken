open Jest;
open ExpectJs;
open Jwt;

describe("sign function", () => {
  let options = Some({ ...emptyOptions, algorithm: HS256, notBefore: "2 days"});
  let secret = `string("secret");
  let payload = `json(Js.Json.object_(Js_dict.empty()));
  let result = sign(~secret, ~options, payload);

  test("should produce a string value", () => {
    expect(result)
    |> toBeTruthy
  });

  test("should produce a token that can be verified", () => {
    Js.log(Jwt.verify(result, secret));
    expect(Jwt.verify(result, secret))
    |> toBeTruthy
  });

  test("should decode a js object with nbf and iat properties", () => {
    expect(Jwt.decode(result))
    |> toContainProperties([|"nbf", "iat"|])
  })
})