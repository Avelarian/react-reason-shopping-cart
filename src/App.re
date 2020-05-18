open Belt;

module Basket = {
  type product = {
    id: int,
    name: string,
    description: string,
    price: int,
    quantity: int,
  };

  type basketRecord = {
    products: array(product),
    total: int,
  };

  let basket = {products: [||], total: 0};

  type action =
    | AddToBasket(product)
    | RemoveFromBasket(product);

  let productsReducer = (state, action) => {
    switch (action) {
    | AddToBasket(element) =>
      switch (
        state.products->Array.getBy(product => element.id === product.id)
        !== None
      ) {
      | false => {
          products: state.products->Array.concat([|element|]),
          total: state.total + element.price,
        }
      | true => {
          products:
            state.products
            ->Array.map(product => {
                product.id === element.id
                  ? {
                    {...product, quantity: product.quantity + 1};
                  }
                  : product
              }),
          total: state.total + element.price,
        }
      }
    | RemoveFromBasket(element) =>
      state.products
      ->Array.getBy(product =>
          element.id === product.id && product.quantity === 1
        )
      !== None
        ? {
          {
            products:
              state.products->Array.keep(product => product.id !== element.id),
            total: state.total - element.price,
          };
        }
        : {
          {
            products:
              state.products
              ->Array.map(product => {
                  product.id === element.id
                    ? {
                      {...product, quantity: product.quantity - 1};
                    }
                    : product
                }),
            total: state.total - element.price,
          };
        }
    };
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(Basket.productsReducer, Basket.basket);

  let products: array(Basket.product) = [|
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
    },
  |];

  <main>
    <h1> "React Reason Shopping Cart"->React.string </h1>
    <div className="container">
      <ul>
        {products
         ->Array.map(product =>
             <li>
               "Img"->React.string
               <div>
                 <strong> product.name->React.string </strong>
                 <p>
                   product.description->React.string
                   " | "->React.string
                   product.quantity->React.int
                 </p>
               </div>
               <button onClick={_ => dispatch(AddToBasket(product))}>
                 "Add to basket"->React.string
               </button>
             </li>
           )
         ->React.array}
      </ul>
      <div className="basketContainer">
        "Basket"->React.string
        <ul>
          "ITEMS"->React.string
          {state.products
           ->Array.map(product =>
               <li>
                 product.name->React.string
                 " | "->React.string
                 product.quantity->React.int
                 <button onClick={_ => dispatch(RemoveFromBasket(product))}>
                   "X"->React.string
                 </button>
               </li>
             )
           ->React.array}
        </ul>
        <ul>
          "TOTALS: "->React.string
          state.total->React.int
          <li> "TVA: "->React.string </li>
          <li> "TOTAL TTC"->React.string </li>
        </ul>
        <div className="actionBox">
          <button> "CANCEL CART"->React.string </button>
          <button> "PAY"->React.string </button>
        </div>
      </div>
    </div>
  </main>;
};