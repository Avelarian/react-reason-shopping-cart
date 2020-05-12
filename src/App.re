// type product = {
//   id: int,
//   img: string,
//   name: string,
//   description: string,
//   price: float,
// };

// type productsList = {products: list(product)};

// type basketList = {products: list(product)};

// type action =
//   | AddToBasket(product)
//   | RemoveFromBasket(product);

// let toString = React.string;

// let addToBasket = (productId, productsList, basketList) => {
//   List.map(p => p.id === productId ? List.append([p], basketList) : basketList, productsList);
//   List.filter(p => p.id !== productId, productsList);
// };

// let removeFromBasket = (productId, basketList, productsList) => {
//   List.map(p => p.id === productId ? List.append([p], productsList) : productsList, basketList);
//   List.filter(p => p.id !== productId, basketList);
// };

[@react.component]
let make = () => {
  let (product, setProduct) = React.useState(() => {});
  let (bList, setBList) = React.useState(() => [product]);
  let (pList, setPList) = React.useState(() => []);

  <main>
    <h1>
      {React.string("React Reason Shopping Cart")}
    </h1>

    <div className="container">
    
      <ul>
        (
          List.map(p =>
            <li>
              <img src=(p.img) />
              <div>
                <strong>{React.string(p.name)}</strong>
                <p>{React.string(p.description)}</p>
              </div>
              <button onClick={_ => setCounter(_ => counter - 1)}>
                {React.string("Add to basket")}
              </button>
            </li>, pList
          )
        )
      </ul>

      <div className="basketContainer">
        {React.string("Basket")}
        <ul>
          {React.string("ITEMS")}
          <li>
            {React.string("2 x xxx")}
          </li>
        </ul>
        
        <ul>
          {React.string("TOTALS")}
          <li>
            {React.string("TVA 20% : 4.00")}
          </li>
          <li>
            {React.string("24.00 TTC")}
          </li>
        </ul>

        <div className="actionBox">
          <button>
            {React.string("Cancel Cart")}
          </button>
          <button>
            {React.string("Pay")}
          </button>
        </div>
      </div>

    </div>
    
  </main>;
};
