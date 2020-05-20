type product = {
  id: int,
  name: string,
  description: string,
  price: int,
  quantity: int,
};

type state = {
  products: array(product),
  total: int,
};

let initialState = {products: [||], total: 0};

type action =
  | Add(product)
  | Remove(product);

let reducer = (state, action) => {
  switch (action) {
  | Add(element) =>
    switch (state.products->Array.getBy(product => element.id === product.id)) {
    | None => {
        products: state.products->Array.concat([|element|]),
        total: state.total + element.price,
      }
    | Some(_) => {
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
  | Remove(element) =>
    switch (
      state.products
      ->Array.getBy(product =>
          element.id === product.id && product.quantity === 1
        )
    ) {
    | Some(_) => {
        products:
          state.products->Array.keep(product => product.id !== element.id),
        total: state.total - element.price,
      }
    | None => {
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
      }
    }
  };
};