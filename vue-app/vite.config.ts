import { fileURLToPath, URL } from 'node:url'
import { resolve } from 'path'

import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
    vue(),
  ],
  build:{
      target: 'es2015',
      rollupOptions: {
          input: 'src/main.ts',
          output: {
          // Could also be a dictionary or array of multiple entry points
          name : 'FwpVue',
          // the proper extensions will be added
          dir: 'dist',
          format: "umd",
        }
     }
  }
})
