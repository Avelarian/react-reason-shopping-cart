open Belt;

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