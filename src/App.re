type product = {
  id: int,
  img: string,
  name: string,
  description: string,
};

[@react.component]
let make = () => {
  <main>
    <h1>
      {React.string("Reason React Shopping Cart")}
    </h1>

    <div className="container">
    
      <ul>
        <li>
          <img src="../assets/img.png" />
          <div>
            <strong>{React.string("Product A")}</strong>
            <p>{React.string("Lorem ipsum")}</p>
          </div>
          <button>
            {React.string("Add to basket")}
          </button>
        </li>
        <li>{React.string("Product B")}</li>
        <li>{React.string("Product C")}</li>
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
