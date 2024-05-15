import {createRoot} from "react-dom/client";
import {Layout} from "./ui-react/layout";
import * as React from "react";

export class ReactApp  {
     constructor(){
        let x:number = 0;
        console.log(x + 100);

        const container = document.getElementById("react-root");
        const root = createRoot(container);
        root.render(React.createElement(Layout, {}));
    }
}