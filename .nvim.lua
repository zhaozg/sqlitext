-- config for https://github.com/zhaozg/neospace
return {
  init = function()
    local capabilities = vim.lsp.protocol.make_client_capabilities()
    capabilities.offsetEncoding = { "utf-8", "utf-16" }

    local setting = require 'neospace.lsp'.setting
    setting('clangd', { settings = {
      capabilities = capabilities
    } })
  end,

  config = function()
    vim.cmd([[
      augroup filetypedetect
        autocmd BufRead,BufNewFile *.h,*.c setlocal filetype=c
      augroup END

      set laststatus=3
      set makeprg=make
      FormatDisable
    ]])
  end
}
