open Belt;

type product = {
  id: int,
  name: string,
  description: string,
  price: float,
  mutable quantity: int,
};

type catalog = array(product);
type basket = array(product);

let initialBasket = [||];

type action =
  | AddToBasket(product)
  | RemoveFromBasket(product);

/* let addToBasket = (basket, item) => {
  
}; */

[@react.component]
let make = () => {
  let (productsArray, setProductsArray) = React.useState(() => [|
    {
      id: 1,
      name: "Product A",
      description: "This is Product A",
      price: 24.99,
      quantity: 0,
    },
    {
      id: 2,
      name: "Product B",
      description: "This is product B",
      price: 4.99,
      quantity: 0,
    }
  |]);

  let (state, dispatch) = React.useReducer((state, action) => switch action {
  | AddToBasket(product) => state->Array.concat([|product|])
  | RemoveFromBasket(product) => state->Array.keep(p => {
    p.id !== product.id
  })
  }, initialBasket);

  <main>
    <h1>
      {"React Reason Shopping Cart" -> React.string}
    </h1>

    <div className="container">
    
      <ul>
        (
          Array.map(productsArray, product => 
            <li>
              {"Img" -> React.string}
              <div>
                <strong>{product.name -> React.string}</strong>
                <p>{product.description -> React.string}{" | "->React.string}{product.quantity->React.int}</p>
              </div>
              <button onClick={_ => dispatch(AddToBasket(product))}> "Add to basket"->React.string </button>
            </li>
          )
        )->React.array
      </ul>

      <div className="basketContainer">
        {"Basket" -> React.string}
        <ul>
          {"ITEMS" -> React.string}
          (
            state->Array.map(product => 
              <li>
                {product.name -> React.string}
                <button onClick={_ => dispatch(RemoveFromBasket(product))}> "X"->React.string </button>
              </li>
            )
          )->React.array
        </ul>
        
        <ul>
          {"TOTALS" -> React.string}
          <li>
            {"TVA: " -> React.string}
          </li>
          <li>
            {"TOTAL TTC" -> React.string}
          </li>
        </ul>

        <div className="actionBox">
          <button>
            {"CANCEL CART" -> React.string}
          </button>
          <button>
            {"PAY" -> React.string}
          </button>
        </div>
      </div>

    </div>
    
  </main>;
};