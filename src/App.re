open Belt;

type product = {
  id: int,
  name: string,
  description: string,
  price: int,
  mutable quantity: int,
};

type productArray = array(product);
let basket = [||];

type action =
  | AddToBasket(product)
  | RemoveFromBasket(product);

let containInBasket = (array, product) => {
  let contains = ref(false);
  array->Array.map(element => {
    if (element.id === product.id) { contains := true };
  })
  contains^;
}

let productUnique = (array, product) => {
  let contains = ref(false);
  array->Array.map(element => {
    if (element.id === product.id && element.quantity === 1) { contains := true };
  })
  contains^;
}

let productsReducer = (state, action) => {
  switch action {
    | AddToBasket(element) => {
      switch (containInBasket(state, element)) {
        | false => {
          Js.log(1);
          setTotal(_ => total + element.price);
          state->Array.concat([|element|]);
        }
        | true => {
          Js.log(2);
          state->Array.map(product => {
            switch (product.id === element.id) {
            | true => { setTotal(_ => total + element.price); { ...product, quantity: product.quantity + 1 }}
            | false => product
            };
          })
        }
      }
    }
    | RemoveFromBasket(element) => {
      switch (productUnique(state, element)) {
      | true => { /*setTotal(_ => total - element.price);*/ state->Array.keep(product => product.id !== element.id)}
      | false => {
        state->Array.map(product => {
          switch (product.id === element.id) {
          | true => { /*setTotal(_ => total - element.price);*/ { ...product, quantity: product.quantity - 1 }}
          | false => product
          };
        })
      }
      };
    }
  };
}

[@react.component]
let make = () => {
  let (products, setProducts) = React.useState(() => [|
  {
    id: 1,
    name: "Product A",
    description: "This is Product A",
    price: 25,
    quantity: 1,
  },
  {
    id: 2,
    name: "Product B",
    description: "This is product B",
    price: 5,
    quantity: 1,
  }
  |]);
  let (total, setTotal) = React.useState(() => 0);
  let (state, dispatch) = React.useReducer(productsReducer, basket);
  
  <main>
    <h1>
      {"React Reason Shopping Cart" -> React.string}
    </h1>

    <div className="container">
    
      <ul>
        (
          products->Array.map(product => 
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
                {product.name -> React.string}{" | "->React.string}{product.quantity -> React.int}
                <button onClick={_ => dispatch(RemoveFromBasket(product))}> "X"->React.string </button>
              </li>
            )
          )->React.array
        </ul>
        
        <ul>
          {"TOTALS: " -> React.string}{total -> React.int}
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