open Belt;

open Basket;

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(productsReducer, Basket.basket);

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
          "TOTAL: "->React.string
          state.total->React.int
          <li>
            "TVA: "->React.string
            {(state.total * 20 / 100)->React.int}
          </li>
          <li>
            "TOTAL TTC: "->React.string
            {(state.total + state.total * 20 / 100)->React.int}
          </li>
        </ul>
        <div className="actionBox">
          <button> "CANCEL CART"->React.string </button>
          <button> "PAY"->React.string </button>
        </div>
      </div>
    </div>
  </main>;
};